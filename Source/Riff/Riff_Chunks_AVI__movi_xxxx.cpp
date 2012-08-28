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
#include <cstring>
//---------------------------------------------------------------------------

//***************************************************************************
// Read
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi_xxxx::Read_Internal ()
{
    if (Global->AVI__movi_FirstDataChunkSize==(int64u)-1)
    {
        Global->AVI__movi_FirstDataChunkMoviOffset=Chunk.File_In_Position-(Parent->Chunk.File_In_Position+Parent->Chunk.Header.Size());
        Global->AVI__movi_FirstDataChunkPosition=Chunk.File_In_Position;
        Global->AVI__movi_FirstDataChunkSize=Chunk.Content.Size;
    }

    //Finding chunkID position
    size_t Pos=( (Chunk.Header.Name>>24)      -'0')*10
              +(((Chunk.Header.Name>>16)&0xFF)-'0');
    if (Pos>Global->AVI__hdrl_strl_strf.size())
        throw exception_valid("incohernecy between header and content ChunkId");
    
    //Reading
    if (Global->GenerateMD5)
    {
        Chunk.Content.Buffer=new int8u[1024*1024];
        while(Chunk.Content.Buffer_Offset<Chunk.Content.Size)
        {
            size_t ToRead=(size_t)Chunk.Content.Size-Chunk.Content.Buffer_Offset;
            if (ToRead>1024*1024)
                ToRead=1024*1024;
            size_t BytesRead=Global->In.Read(Chunk.Content.Buffer, ToRead);
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

            if (Global->AVI__hdrl_strl_strf[Pos]->MD5==NULL)
            {
                Global->AVI__hdrl_strl_strf[Pos]->MD5=new MD5Context;
                MD5Init(Global->AVI__hdrl_strl_strf[Pos]->MD5);
            }
            MD5Update(Global->AVI__hdrl_strl_strf[Pos]->MD5, Chunk.Content.Buffer, (unsigned int)BytesRead);
        }
        if (Chunk.Content.Buffer_Offset<Chunk.Content.Size)
            throw exception_read();
        delete[] Chunk.Content.Buffer; Chunk.Content.Buffer=NULL;
        Chunk.Content.Buffer_Offset=0;
    }
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi_xxxx::Modify_Internal ()
{
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi_xxxx::Write_Internal ()
{
}


