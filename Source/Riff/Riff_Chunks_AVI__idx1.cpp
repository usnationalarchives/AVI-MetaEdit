// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Riff/Riff_Chunks.h"
//---------------------------------------------------------------------------

//***************************************************************************
// AVI_ idx1
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__idx1::Read_Internal ()
{
    if (Global->AVI__idx1_Pointer)
        throw exception_read_chunk("2 idx1 chunks, not supported");
        
    Global->AVI__idx1_Pointer=this;

    //Reading
    Read_Internal_ReadAllInBuffer();
    
    if (Chunk.Content.Size<16)
        return;

    if (Global->AVI__movi_FirstDataChunkSize==(int64u)-1)
        throw exception_read_chunk("idx1 is before movi chunk, or movi chunk has no frame, not supported");

    //Parsing
    for (Chunk.Content.Buffer_Offset=0; Chunk.Content.Buffer_Offset+16<=Chunk.Content.Size; Chunk.Content.Buffer_Offset+=16)
    {
        int32u ChunkId=BigEndian2int32u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset);
        bool IsOk;
        switch (ChunkId&0x0000FFFF)
        {
            case Elements::AVI__movi___db : 
            case Elements::AVI__movi___dc : 
            case Elements::AVI__movi___pc : 
            case Elements::AVI__movi___wb : 
                                            IsOk=true;
                                            break;
            default                       : IsOk=false;
        }
        if (IsOk)
            break;
    }
    if (Chunk.Content.Buffer_Offset+16>Chunk.Content.Size)
        throw exception_read_chunk("index data has no frame reference?");

    int32u Offset=LittleEndian2int32u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset+8);
    int32u Size=LittleEndian2int32u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset+12);

    if (Size!=Global->AVI__movi_FirstDataChunkSize)
        throw exception_read_chunk("index data (size) not coherent");
    int64u movi_Position=(int64u)-1;
    for (std::set<void*>::iterator movi=Global->AVI__movi_Pointers.begin(); movi!=Global->AVI__movi_Pointers.end(); movi++)
    {
        if (((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position<movi_Position)
            movi_Position=((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position;
    }
    if (Offset==4+Global->AVI__movi_FirstDataChunkMoviOffset)
        Global->AVI__idx1_IsAbsolute=false;
    else if (Offset==Global->AVI__movi_FirstDataChunkPosition)
        Global->AVI__idx1_IsAbsolute=true;
    else    
        throw exception_read_chunk("index data (position) is not coherent");
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__idx1::Modify_Internal ()
{
    //Integrity
    if (Global->AVI__movi_Pointers.empty())
        throw exception_valid("indx: movi chunk is not found");

    std::set<void*>::iterator movi=Global->AVI__movi_Pointers.begin();

    if (((Riff_AVI__movi*)(*movi))->Chunk.Content.IsModified || ((Riff_AVI__movi*)(*movi))->Chunk.Content.Size_IsModified)
        throw exception_valid("indx: modified movi chunk is not supported");

    if (!Global->AVI__idx1_IsAbsolute)
        return;    
        
    int64u movi_Position=((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position;
    int64s Difference=((Riff_AVI__movi*)(*movi))->Chunk.File_Out_Position-((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position;
    Difference-=Global->AVI__idx1_Difference;
    if (Difference==0)
        return;

    for (Chunk.Content.Buffer_Offset=0; Chunk.Content.Buffer_Offset+16<=Chunk.Content.Size; Chunk.Content.Buffer_Offset+=16)
    {
        int32u Offset=LittleEndian2int32u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset+8);
        Offset+=Difference;
        int32u2LittleEndian(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset+8, Offset);
    }

    Global->AVI__idx1_Difference+=Difference;
    
    Chunk.Content.IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__idx1::Write_Internal ()
{
}
