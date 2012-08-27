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
void Riff_AVI__hdrl_strl_indx::Read_Internal ()
{
    //Filling
    Global->AVI__hdrl_strl_indx_Pointers.insert(this);

    //Reading
    Read_Internal_ReadAllInBuffer();

    //Parsing
    int32u Entry_Count, ChunkId;
    int16u LongsPerEntry;
    int8u  IndexType, IndexSubType;
    Get_L2 (LongsPerEntry);
    Get_L1 (IndexSubType);
    Get_L1 (IndexType);
    Get_L4 (Entry_Count);
    Get_C4 (ChunkId);

    //Integrity
    if (LongsPerEntry!=4 || (IndexSubType&0xFE) || IndexType!=0x00 || 24+Entry_Count*16>Chunk.Content.Size)
        throw exception_valid("hdrl_strl_indx form is not supported");

    //Parsing
    Skip_XX(12); //Reserved
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        int64u Offset;
        Get_L8 (Offset);
        Skip_XX(8); //Size + Duration

        //Filling
        Global->AVI__hdrl_strl_indx_In_Position_Indexes_List.push_back(Offset);
        Global->AVI__movi___ix_WithFields[ChunkId]=(IndexSubType&0x01)?true:false;
    }
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_indx::Modify_Internal ()
{
    //EntryCount
    int32u Entry_Count=LittleEndian2int32u(Chunk.Content.Buffer+4);

    bool IsChanged=false;
    Chunk.Content.Buffer_Offset=24;
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        int64u Value=LittleEndian2int64u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset);
        /*
        for (std::set<void*>::iterator movi=Global->AVI__movi_Pointers.begin(); movi!=Global->AVI__movi_Pointers.end(); movi++)
            if (Value>=((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position && Value<((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position+((Riff_AVI__movi*)(*movi))->Chunk.Content.Size)
            {
                if (((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position!=((Riff_AVI__movi*)(*movi))->Chunk.File_Out_Position)
                {
                    Value-=((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position;
                    Value+=((Riff_AVI__movi*)(*movi))->Chunk.File_Out_Position;
                    int64u2LittleEndian(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset, Value);
                    IsChanged=true;
                }
                break;
            }
        */
        for (std::set<void*>::iterator ix=Global->AVI__movi___ix_Pointers.begin(); ix!=Global->AVI__movi___ix_Pointers.end(); ix++)
            if (Value==((Riff_AVI__movi___ix*)(*ix))->Chunk.File_In_Position)
            {
                if (((Riff_AVI__movi___ix*)(*ix))->Chunk.File_Out_Position!=((Riff_AVI__movi___ix*)(*ix))->Chunk.File_In_Position)
                {
                    int64u2LittleEndian(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset, ((Riff_AVI__movi___ix*)(*ix))->Chunk.File_Out_Position);
                    IsChanged=true;
                }
                break;
            }
        Chunk.Content.Buffer_Offset+=16;
    }

    if (IsChanged)
        Chunk.Content.IsModified=true;
    //Chunk.Content.Size_IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_indx::Write_Internal ()
{
}


