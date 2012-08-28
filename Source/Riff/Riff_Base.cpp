// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Riff/Riff_Base.h"
#include "Riff/Riff_Chunks.h" //Needed for ds64
#include <iostream>
#include <cstring>
using namespace std;
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// chunk class
//***************************************************************************

//---------------------------------------------------------------------------
bool Riff_Base::chunk::IsFiller()
{
    switch (Header.Name)
    {
        case Elements::AVI__filr :
        case Elements::AVI__FILR :
        case Elements::AVI__fllr :
        case Elements::AVI__FLLR :
        case Elements::AVI__junk :
        case Elements::AVI__JUNK :
        case Elements::AVI__junq :
        case Elements::AVI__JUNQ :
        case Elements::AVI__pad_ :
        case Elements::AVI__PAD_ :
                                    return true;
        default                  :  return false;
    }
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Riff_Base::Riff_Base (Riff_Base* Parent_)
{
    //Chunk
    Parent=Parent_;

    //Global handler
    Global=Parent_?Parent->Global:NULL;
}

//---------------------------------------------------------------------------
Riff_Base::~Riff_Base ()
{
    for (size_t Pos=0; Pos<Subs.size(); Pos++)
        delete Subs[Pos]; //Subs[Pos]=NULL;
}

//***************************************************************************
// Read
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_Base::Read (const chunk &Chunk_In)
{
    //Configuring chunk data
    Chunk=Chunk_In;

    //Trace
    if (Parent)
    {
        bool IsOk=true;
        if (Parent->Chunk.Header.Name==Elements::AVI__movi)
        {
            switch (Chunk.Header.Name&0x0000FFFF)
            {
                case Elements::AVI__movi___db : 
                case Elements::AVI__movi___dc : 
                case Elements::AVI__movi___pc : 
                case Elements::AVI__movi___wb : 
                                                IsOk=false;
                                                break;
                default                       : ;
            }
        }

        if (IsOk)
        {
            //Offset
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x10000000)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x1000000)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x100000)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x10000)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x1000)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x100)
                Global->Trace<<'0';
            if (Global->In.Position_Get()-Chunk.Header.Size()<0x10)
                Global->Trace<<'0';
            Global->Trace<<Ztring::ToZtring(Global->In.Position_Get()-Chunk.Header.Size(), 16)<<' ';

            //Chunk name
            for (size_t Pos=1; Pos<Level(); Pos++)
                Global->Trace<<"     ";
            Global->Trace<<Ztring().From_CC4(Chunk.Header.Name);
        
            //Size
            if (Level()<4)
                for (size_t Pos=0; Pos<4-Level(); Pos++)
                    Global->Trace<<"     ";
            //for (size_t Pos=0; Pos<Level(); Pos++)
                Global->Trace<<' ';
            Global->Trace<<"("<<Chunk.Header.Size()+Chunk.Content.Size<<" bytes)";
        
            Global->Trace<<endl;
        }
    }

    //Specific to a chunk
    Read_Internal();

    //Parsing subs
    if (Chunk.Header.IsList)
    {
        while (Global->In.Position_Get()<Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size && Chunk.ShouldParse)
        {
            chunk NewChunk;
            if (!Read_Header(NewChunk))
                return;
            
            Riff_Base* Sub=NULL;
            size_t Sub_Pos=(size_t)-1; //Will not be used
            Insert_Internal (NewChunk.Header.Name, Sub, Sub_Pos);
            if (Sub==NULL)
                Sub=new Riff_Base(this);
            Sub->Read(NewChunk);
            Subs.push_back(Sub);
            if (NewChunk.Content.IsModified)
                Chunk.Content.IsModified=true;
            if (NewChunk.Content.Size_IsModified)
                Chunk.Content.Size_IsModified=true;
            if (!NewChunk.Content.IsModified && Chunk.Content.Size>=0x1000000)
                Chunk.IsMoovable=false;
            Seek_Internal();
        }
    }

    //Testing malformed files (padding)
    bool File_in_Chunk_Content_HasPadding=false;
    if (Chunk.Content.Size%2)
    {
        Global->In.GoTo(Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size);
        int8u Temp[1];
        if (Global->In.Position_Get()==Global->In.Size_Get())
            Temp[0]='A'; //Malformed
        else if (Global->In.Read(Temp, 1)<1)
            throw exception_read();
        Global->CS.Enter();
        Global->Progress=(float)Global->In.Position_Get()/Global->In.Size_Get();
        if (Global->Canceling)
        {
            Global->CS.Leave();
            throw exception_canceled();
        }
        Global->CS.Leave();
        //SleeperThread::msleep(20);
        if ((Temp[0]<'A' || Temp[0]>'z') && Temp[0]!=' ')
            File_in_Chunk_Content_HasPadding=true;
        else
        {
            if (!Global->NoPadding_Accept)
                throw exception_valid("padding");
            
            //Log
            Global->NoPadding_IsCorrected=true;

            Chunk.Content.IsModified=true;
            Chunk.Content.Size_IsModified=true;
        }
    }

    //Positioning
    Global->In.GoTo(Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size+(File_in_Chunk_Content_HasPadding?1:0));

    //We want at least a AVI_ chunk at the begining
    if (Global->In.Position_Get()>=Global->In.Size_Get() && Global->AVI_==NULL)
        throw exception_valid("no AVI header");
}

//---------------------------------------------------------------------------
bool Riff_Base::Read_Header (chunk &NewChunk)
{
    int8u Temp[4];
   
    //Chunk position
    NewChunk.File_In_Position=Global->In.Position_Get();

    //Chunk name
    if (Global->In.Position_Get()+8>Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size)
        throw exception_valid("small");
    if (Global->In.Read(Temp, 4)<4)
        throw exception_read();
    NewChunk.Header.Name=CC4(Temp);

    //Chunk size
    if (Global->In.Position_Get()+4>Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size)
        throw exception_valid("small");
    if (Global->In.Read(Temp, 4)<4)
        throw exception_read();
    NewChunk.Content.Size=LittleEndian2int32u(Temp);
    if (Global->In.Position_Get()+NewChunk.Content.Size>Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size)
        throw exception_valid("truncated");
    
    //List management (if present)
    if (NewChunk.Header.Name==Elements::LIST || NewChunk.Header.Name==Elements::RIFF)
    {
        if (Global->In.Position_Get()+4>Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size)
            throw exception_valid("small");
        if (Global->In.Read(Temp, 4)<4)
            throw exception_read();
        NewChunk.Header.IsList=true;
        NewChunk.Header.Name=CC4(Temp);
        NewChunk.Content.Size-=4;
    }
    
    //Null padding / Junk management
    if (NewChunk.Header.Name==0x00000000)
    {
        NewChunk.Content.Size=Chunk.File_In_Position+Chunk.TotalSize()-NewChunk.File_In_Position;
        NewChunk.Header.IsOpaqueData=true;
        Global->In.GoTo(-8, File::FromCurrent);
    }

    return true;
}

//---------------------------------------------------------------------------
bool Riff_Base::ClearJunk ()
{
    for (size_t Pos=0; Pos<Subs.size(); Pos++)
    {
        if (Subs[Pos]->Chunk.IsFiller())
        {
            Subs.erase(Subs.begin()+Pos);
            Pos--;
        }
        else  if (Subs[Pos]->Chunk.Header.Name!=Elements::AVI__movi) //Should not modify movi chunks
            Subs[Pos]->ClearJunk();
    }
    
    return true;
}

//---------------------------------------------------------------------------
void Riff_Base::UpdateIndexes ()
{
    //Updating indexes
    if (Global->AVI__idx1_Pointer)
        ((Riff_AVI__idx1*)(Global->AVI__idx1_Pointer))->Modify();
    for (std::set<void*>::iterator indx=Global->AVI__hdrl_strl_indx_Pointers.begin(); indx!=Global->AVI__hdrl_strl_indx_Pointers.end(); indx++)
        ((Riff_AVI__hdrl_strl_indx*)(*indx))->Modify();
    for (std::set<void*>::iterator ix=Global->AVI__movi___ix_Pointers.begin(); ix!=Global->AVI__movi___ix_Pointers.end(); ix++)
        ((Riff_AVI__movi___ix*)(*ix))->Modify();
}

//---------------------------------------------------------------------------
bool Riff_Base::InsertVirtual (size_t Pos, int64u Size)
{
    Subs.insert(Subs.begin()+Pos, new Riff_Base(this));
    Subs[Pos]->Chunk.Header.IsOpaqueData=true;
    Subs[Pos]->Chunk.Content.Size=Size;
    Subs[Pos]->Chunk.IsMoovable=false;
    Subs[Pos]->Chunk.File_In_Position=Global->In.Position_Get();

    return true;
}

//---------------------------------------------------------------------------
bool Riff_Base::InsertJunk (size_t Pos, int64u Size)
{
    Subs.insert(Subs.begin()+Pos, new Riff_AVI__JUNK(this));
    Subs[Pos]->Chunk.Header.Name=Elements::AVI__JUNK;
    Subs[Pos]->Chunk.Content.Size=Size;
    Subs[Pos]->Chunk.Content.Buffer=new int8u[(size_t)Subs[Pos]->Chunk.Content.Size];
    memset(Subs[Pos]->Chunk.Content.Buffer, 0x00, (size_t)Subs[Pos]->Chunk.Content.Size);
    Subs[Pos]->Chunk.Content.IsModified=true;
    Subs[Pos]->Chunk.Content.Size_IsModified=true;

    Chunk.Content.Size+=Subs[Pos]->Chunk.Header.Size()+Subs[Pos]->Chunk.Content.Size;
    Chunk.Content.Size_IsModified=true;
    return true;
}

//---------------------------------------------------------------------------
bool Riff_Base::CanOverwrite (int64u &File_Out_Position, int64u &SizeToRead, int64u &ShouldAddFilling, bool Refactorize)
{
    Chunk.File_Out_Position=File_Out_Position;

    if (!Subs.empty())
    {
        if (!Chunk.IsMoovable && !Refactorize && Chunk.File_In_Position!=File_Out_Position)
        {
            if (Chunk.File_In_Position<File_Out_Position)
                return false; //Must write the whole file    
            int64u Filler_Size=Chunk.File_In_Position-File_Out_Position;
            if (Filler_Size<8)
                return false; //Must write the whole file    
            SizeToRead+=Filler_Size;
            File_Out_Position+=Filler_Size;
            ShouldAddFilling=Filler_Size;
        }
        
        File_Out_Position+=Chunk.Header.Size();
        SizeToRead+=Chunk.Header.Size();
        int64u Content_Size=0;
        for (size_t Pos=0; Pos<Subs.size(); Pos++)
        {
            int64u ShouldAddFilling=0;
            if (!Subs[Pos]->CanOverwrite(File_Out_Position, SizeToRead, ShouldAddFilling, Refactorize))
                return false;
            if (!Refactorize && ShouldAddFilling)
            {
                InsertJunk(Pos, ShouldAddFilling-8);
                Content_Size+=ShouldAddFilling;
                File_Out_Position+=ShouldAddFilling;
                Subs[Pos]->Chunk.File_Out_Position=Subs[Pos+1]->Chunk.File_Out_Position;
                Subs[Pos+1]->Chunk.File_Out_Position+=ShouldAddFilling;
                Pos++;
            }
            Content_Size+=Subs[Pos]->Chunk.Header.Size()+Subs[Pos]->Chunk.Content.Size;
            if (Subs[Pos]->Chunk.Content.Size%2)
                Content_Size++;
        }
        if (Content_Size!=Chunk.Content.Size)
        {
            if (!Refactorize && Chunk.Header.IsList && Content_Size+8<=Chunk.Content.Size && Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size!=Global->File_Size)
            {
                //Trying to keep LIST size as before
                InsertJunk(Subs.size(), Chunk.Content.Size-(Content_Size+8));
                Content_Size+=Subs[Subs.size()-1]->Chunk.Header.Size()+Subs[Subs.size()-1]->Chunk.Content.Size;
                File_Out_Position+=Subs[Subs.size()-1]->Chunk.Header.Size()+Subs[Subs.size()-1]->Chunk.Content.Size;
            }
            else
            {
                Chunk.Content.Size=Content_Size;
                if (Content_Size%2)
                    Chunk.Content.Size++;
                Chunk.Content.Size_IsModified=true;
            }
        }
        return true;
    }

    if (Chunk.IsMoovable)
    {
        if (Chunk.File_In_Position!=File_Out_Position)
            SizeToRead+=Chunk.Header.Size()+Chunk.Content.Size;
    }
    else if (!Refactorize)
    {
        if (Chunk.File_In_Position!=File_Out_Position)
        {
            if (Chunk.File_In_Position<File_Out_Position)
                return false; //Must write the whole file    
            int64u Filler_Size=Chunk.File_In_Position-File_Out_Position;
            if (Filler_Size<8)
                return false; //Must write the whole file    
            SizeToRead+=Filler_Size;
            ShouldAddFilling=Filler_Size;
        }
    }

    File_Out_Position+=Chunk.Header.Size()+Chunk.Content.Size;
    if (Chunk.Content.Size%2)
        File_Out_Position++;

    return true;
}

//---------------------------------------------------------------------------
bool Riff_Base::WriteOut (bool Refactorize)
{
    //Header
    if (Level() && Chunk.Header.Size())
    {
        if (!Refactorize && Chunk.File_In_Position==Global->Out.Position_Get())
        {
            if (Chunk.Content.Size_IsModified)
            {
                Global->Out.GoTo(4, File::FromCurrent);
                int8u* Buffer=new int8u[4];
                int32u2LittleEndian(Buffer, Chunk.Content.Size+Chunk.Header.Size()-8);
                Global->Out.Write(Buffer, 4); 
                delete[] Buffer;
                if (Chunk.Header.IsList)
                    Global->Out.GoTo(4, File::FromCurrent);
            }
            else
                Global->Out.GoTo(Chunk.Header.Size(), File::FromCurrent);
        }
        else
        {
            int8u* Buffer=new int8u[Chunk.Header.Size()];
            if (Chunk.Header.IsList)
            {
                int32u2BigEndian(Buffer, (Chunk.Header.Name==Elements::AVI_ || Chunk.Header.Name==Elements::AVIX)?Elements::RIFF:Elements::LIST);
                int32u2LittleEndian(Buffer+4, 4+Chunk.Content.Size);
                int32u2BigEndian(Buffer+8, Chunk.Header.Name);
            }
            else
            {
                int32u2BigEndian(Buffer, Chunk.Header.Name);
                int32u2LittleEndian(Buffer+4, Chunk.Content.Size);
            }
            Global->Out.Write(Buffer, Chunk.Header.Size()); 
            delete[] Buffer;
        }
    }

    //Subs
    if (!Subs.empty())
    {
        for (size_t Pos=0; Pos<Subs.size(); Pos++)
        {
            if (!Subs[Pos]->WriteOut(Refactorize))
                return false;
        }
        return true;
    }

    //Content
    if (Chunk.Content.IsModified || Chunk.File_In_Position+Chunk.Header.Size()!=Global->Out.Position_Get() || Refactorize)
    {
        if (Chunk.Content.Buffer==NULL)
        {
            Global->In.GoTo(Chunk.File_In_Position+Chunk.Header.Size());
            int8u* Buffer=new int8u[512*1024];
            int64u Chunk_Offset=0;
            while (Chunk_Offset<Chunk.Content.Size)
            {
                size_t BytesRead=Global->In.Read(Buffer, (Chunk.Content.Size-Chunk_Offset)<32768?(Chunk.Content.Size-Chunk_Offset):32768);
                if (BytesRead==0)
                    throw exception_write("Can not read input file, output file may be CORRUPTED");
                size_t BytesWritten=Global->Out.Write(Buffer, BytesRead);
                Chunk_Offset+=BytesRead;

                Riff_Base* Temp=Parent;
                while (Temp->Parent)
                    Temp=Temp->Parent;
                Global->CS.Enter();
                if ((float)Global->Out.Position_Get()<Temp->Chunk.Content.Size)
                    Global->Progress=(float)Global->Out.Position_Get()/Temp->Chunk.Content.Size;
                else
                    Global->Progress=(float)0.99;
                if (Global->Canceling)
                {
                    Global->CS.Leave();
                    throw exception_canceled();
                }
                Global->CS.Leave();

            }
            delete[] Buffer;
            if (Chunk.Content.Size%2)
                Global->Out.Write((int8u*)"\x00", 1);
        }
        else if (Chunk.Content.Size)
            Global->Out.Write(Chunk.Content.Buffer, Chunk.Content.Size);
        if (Chunk.Content.Size%2)
            Global->Out.Write((int8u*)"\x00", 1);
    }
    else
        Global->Out.GoTo(Chunk.Content.Size+((Chunk.Content.Size%2)?1:0), File::FromCurrent);

    return true;
}

//---------------------------------------------------------------------------
void Riff_Base::Read_Internal_ReadAllInBuffer ()
{
    //Creating buffer
    if (Chunk.Content.Size==0) //Chunk.Content.Size may be set to something else for customizing
        Chunk.Content.Size=Chunk.Content.Size;
    if (Chunk.Content.Size>0x1000000)
        throw exception_read_chunk("non-video data exceeds available memory");

    delete Chunk.Content.Buffer; Chunk.Content.Buffer=NULL;

    try
    {
        Chunk.Content.Buffer=new int8u[(size_t)Chunk.Content.Size];
    }
    catch(...)
    {
        throw exception_read_chunk("non-video data exceeds available memory");
    }

    //Reading
    while(Chunk.Content.Buffer_Offset<Chunk.Content.Size)
    {
        size_t BytesRead=Global->In.Read(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset, (size_t)Chunk.Content.Size-Chunk.Content.Buffer_Offset);
        if (BytesRead==0)
            break; //Read is finished
        Global->CS.Enter();
        Global->Progress=(float)Global->In.Position_Get()/Global->In.Size_Get();
        if (Global->Canceling)
        {
            Global->CS.Leave();
            throw exception_canceled();
        }
        Global->CS.Leave();
        Chunk.Content.Buffer_Offset+=BytesRead;
    }
    if (Chunk.Content.Buffer_Offset<Chunk.Content.Size)
        throw exception_read();
    Chunk.Content.Buffer_Offset=0;
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_Base::Modify (int32u Chunk_Name_1, int32u Chunk_Name_2, int32u Chunk_Name_3)
{
    if (Chunk_Name_1==0x00000000)
        Modify_Internal();
    else
        Modify_Internal_Subs(Chunk_Name_1, Chunk_Name_2, Chunk_Name_3);
}

//---------------------------------------------------------------------------
void Riff_Base::Modify_Internal_Subs (int32u Chunk_Name_1, int32u Chunk_Name_2, int32u Chunk_Name_3)
{
    //Parsing subs
    bool Sub_IsFound=false;
    size_t Sub_Pos=0;
    for (; Sub_Pos<Subs.size(); Sub_Pos++)
        if (Subs[Sub_Pos]->Chunk.Header.Name==Chunk_Name_1)
            break;
    
    //Handling when sub is not present
    int64u OldContentSize;
    if (Sub_Pos>=Subs.size())
    {
        Sub_Pos=Subs.size();
        OldContentSize=0;
        if (!Insert(Chunk_Name_1))
            return; //Inserting is not supported
        Modify_Internal_Subs(Chunk_Name_1, Chunk_Name_2, Chunk_Name_3);
        return;
    }
    else
    {
        //Modifying
        OldContentSize=Subs[Sub_Pos]->Chunk.Header.Size()+Subs[Sub_Pos]->Chunk.Content.Size;
        Subs[Sub_Pos]->Modify(Chunk_Name_2, Chunk_Name_3, 0x00000000);
    }

    if (Subs[Sub_Pos]->Chunk.Content.IsModified)
        Chunk.Content.IsModified=true;
    if (Subs[Sub_Pos]->Chunk.Content.Size_IsModified || Subs[Sub_Pos]->Chunk.Content.IsRemovable)
    {
        int64u NewContentSize=Subs[Sub_Pos]->Chunk.Content.IsRemovable?0:(Subs[Sub_Pos]->Chunk.Header.Size()+Subs[Sub_Pos]->Chunk.Content.Size);
        if (Sub_Pos+1<Subs.size() && Subs[Sub_Pos+1]->Chunk.IsFiller())
        {
            if (NewContentSize>OldContentSize) //Bigger
            {
                size_t AdditionalSize=NewContentSize-OldContentSize;
                if (AdditionalSize<=Subs[Sub_Pos+1]->Chunk.Content.Size)
                {
                    Subs[Sub_Pos+1]->Chunk.Content.Size-=AdditionalSize;
                    Subs[Sub_Pos+1]->Chunk.Content.IsModified=true;
                    Subs[Sub_Pos+1]->Chunk.Content.Size_IsModified=true;
                }
                else
                {
                    Chunk.Content.Size-=Subs[Sub_Pos+1]->Chunk.Header.Size()+Subs[Sub_Pos+1]->Chunk.Content.Size;
                    Chunk.Content.Size_IsModified=true;
                    Subs.erase(Subs.begin()+Sub_Pos+1);
                }
            }
            else if (NewContentSize<OldContentSize) //Smaller
            {
                Subs[Sub_Pos+1]->Chunk.Content.Size+=OldContentSize-NewContentSize;
                delete[] Subs[Sub_Pos+1]->Chunk.Content.Buffer; Subs[Sub_Pos+1]->Chunk.Content.Buffer=new int8u[Subs[Sub_Pos+1]->Chunk.Content.Size];
                memset(Subs[Sub_Pos+1]->Chunk.Content.Buffer, 0x00, Subs[Sub_Pos+1]->Chunk.Content.Size);
                Subs[Sub_Pos+1]->Chunk.Content.IsModified=true;
                Subs[Sub_Pos+1]->Chunk.Content.Size_IsModified=true;
            }
        }
        else
        {
            Chunk.Content.Size-=OldContentSize;
            Chunk.Content.Size+=NewContentSize;
            Chunk.Content.Size_IsModified=true;
        }
    }
    if (Subs[Sub_Pos]->Chunk.Content.IsRemovable)
    {
        Chunk.Content.IsModified=true;
        Chunk.Content.Size_IsModified=true;
        Subs.erase(Subs.begin()+Sub_Pos);
        Sub_Pos--;
        if (Subs.empty())
            Chunk.Content.IsRemovable=true;
    }
}

//***************************************************************************
// Insert
//***************************************************************************

//---------------------------------------------------------------------------
bool Riff_Base::Insert (int32u Chunk_Name)
{
    Riff_Base* NewRiff=NULL;
    size_t Chunk_Pos=(size_t)-1;
    Insert_Internal(Chunk_Name, NewRiff, Chunk_Pos);     
    
    if (NewRiff==NULL)
        return false; //Not supported

    NewRiff->Chunk.Header.Name=Chunk_Name;
    NewRiff->Chunk.Header.IsModified=true;
    NewRiff->Modify();
    if (NewRiff->IsRemovable())
    {
        delete NewRiff; //Chunk=NULL;
        return false; //Not needed
    }

    if (Chunk_Pos<Subs.size())
    {
        if (Chunk_Pos<Subs.size() && Subs[Chunk_Pos]->Chunk.IsFiller())
        {
            if (NewRiff->Chunk.TotalSize()<=Subs[Chunk_Pos]->Chunk.Content.Size) //Smaller than next junk chunk content size
            {
                Subs[Chunk_Pos]->Chunk.Content.Size-=NewRiff->Chunk.TotalSize();
                Subs[Chunk_Pos]->Chunk.Content.IsModified=true;
                Subs[Chunk_Pos]->Chunk.Content.Size_IsModified=true;
            }
            else if (NewRiff->Chunk.TotalSize()==Subs[Chunk_Pos]->Chunk.TotalSize()) //Equal to junk chunk size
            {
                Subs.erase(Subs.begin()+Chunk_Pos);
            }
            else //Bigger than next junk chunk content size
            {
                Chunk.Content.Size+=NewRiff->Chunk.TotalSize();
                Chunk.Content.Size-=Subs[Chunk_Pos]->Chunk.TotalSize();
                Chunk.Content.Size_IsModified=true;
                Subs.erase(Subs.begin()+Chunk_Pos);
            }
        }
        else
        {
            Chunk.Content.Size+=NewRiff->Chunk.TotalSize();
            Chunk.Content.Size_IsModified=true;
        }
        Subs.insert(Subs.begin()+Chunk_Pos, NewRiff);
        Chunk.Content.IsModified=true;
    }
    else
    {
        Chunk.Content.Size+=NewRiff->Chunk.TotalSize();
        Chunk.Content.Size_IsModified=true;
        Subs.push_back(NewRiff);
        Chunk.Content.IsModified=true;
    }

    return true;
}
    
//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_Base::Write ()
{
    //Check if we can write over the current file
    int64u File_Out_Position=0;
    int64u SizeToRead=0;
    int64u ShouldAddFilling=0;
    bool   CloseIn=true;
    if (!CanOverwrite(File_Out_Position, SizeToRead, ShouldAddFilling, false))
    {
        //Handling the problem
        ClearJunk();

        //Adding some padding
        if (12+Subs[0]->Chunk.Content.Size+8<=0xFFFFFFF2) //AVI block size + 2*minimal filler size
        {
            CanOverwrite(File_Out_Position, SizeToRead, ShouldAddFilling, true);
            int64u FillerSize_Before=0xFFFFFFF2-(12+Subs[0]->Chunk.Content.Size+8);
            int64u FillerSize_After=0;
            if (FillerSize_Before>RIFF_AVI__JUNK_DefaultSise)
            {
                if (Subs.size()>1 && FillerSize_Before>RIFF_AVI__JUNK_DefaultSise+8)
                {
                    FillerSize_After=FillerSize_Before-(RIFF_AVI__JUNK_DefaultSise+8);
                    if (FillerSize_After>RIFF_AVI__JUNK_DefaultSise)
                        FillerSize_After=RIFF_AVI__JUNK_DefaultSise;
                }
                FillerSize_Before=RIFF_AVI__JUNK_DefaultSise;
            }

            size_t movi_Pos=Subs[0]->Subs_Pos_Get(Elements::AVI__movi);
            if (movi_Pos!=(size_t)-1)
                Subs[0]->InsertJunk(movi_Pos, FillerSize_Before);
            if (FillerSize_After)
                Subs[0]->InsertJunk(Subs[0]->Subs.size(), FillerSize_After);
        }

        //Parsing again
        File_Out_Position=0;
        SizeToRead=0;
        ShouldAddFilling=0;
        CanOverwrite(File_Out_Position, SizeToRead, ShouldAddFilling, true);
        CloseIn=false;
    }
    if (Subs[0]->Chunk.Content.Size>0xFFFFFFF2)
    {
        if (Subs.size()>1)
            throw exception_write("Moving a frame from AVI chunk to AVIX chunk is not supported");
        else
            throw exception_write("Creation of OpenDML from non-OpenDML file is not supported"); //File size would be too big (and --reject-avi2avix option)
    }

    //Updating indexes
    UpdateIndexes();

    if (CloseIn && SizeToRead>=0x10000000)
    {
        //Handling the problem
        ClearJunk();

        //Parsing again
        File_Out_Position=0;
        SizeToRead=0;
        ShouldAddFilling=0;
        CanOverwrite(File_Out_Position, SizeToRead, ShouldAddFilling, true);
        CloseIn=false;

        //Updating indexes
        UpdateIndexes();
    }
        
    //Initializing
    if (CloseIn)
    {
        //Real writing
        Global->In.Close();
        if (!Global->Out.Open(Global->File_Name, File::Access_Read_Write))
            throw exception_write("Can not open input file in read/write mode");
    }
    else
    {
        //Real writing
        if (!Global->Out.Create(Global->File_Name+".tmp", false))
            throw exception_write("Can not create temporary file");
    }
    
    //Writing
    if (!WriteOut(!CloseIn))
    {
        //Handling the problem
        Global->In.Close();
        Global->Out.Close();
        if (CloseIn)
            throw exception_write("Can not write input file, file may be CORRUPTED");
        else
        {
            File::Delete(Global->File_Name);
            throw exception_write("Can not write temporary file");
        }
        return;
    }
    Global->Out.Truncate();

    //Cleanup
    Global->In.Close();
    Global->Out.Close();

    if (!CloseIn)
    {
        //Renaming files
        if (!File::Delete(Global->File_Name))
            throw exception_write("Original file can't be deleted");
        if (!File::Move(Global->File_Name+".tmp", Global->File_Name))
            throw exception_write("Temporary file can't be renamed");
    }

    return;
}

//---------------------------------------------------------------------------
void Riff_Base::Read_Internal ()
{
    if (!Chunk.IsFiller())
    {
        Global->UnprocessedChunks.insert(Chunk.Header.Name);
    }
        
    Read_Internal_ReadAllInBuffer();
}

//---------------------------------------------------------------------------
void Riff_Base::Seek_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_Base::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    Chunk=NULL; 
    Chunk_Pos=(size_t)-1; 
}

//---------------------------------------------------------------------------
void Riff_Base::Write_Internal ()
{
}

//---------------------------------------------------------------------------
size_t Riff_Base::Subs_Pos_Get (int32u Element)
{
    size_t Subs_Pos=0;
    for (; Subs_Pos<Subs.size(); Subs_Pos++)
        if (Subs[Subs_Pos]->Chunk.Header.Name==Element)
            break;
    if (Subs_Pos<Subs.size())
        return Subs_Pos;
    else
        return (size_t)-1;
}
