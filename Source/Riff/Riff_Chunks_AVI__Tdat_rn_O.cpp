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
void Riff_AVI__Tdat_rn_O::Read_Internal ()
{
    //Integrity
    if (Global->iXML)
        throw exception_valid("2 rn_O chunks");

    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    Ztring Value;
    bool IsOk=true;
    for (Chunk.Content.Buffer_Offset=0; Chunk.Content.Buffer_Offset<Chunk.Content.Size; Chunk.Content.Buffer_Offset++)
        if (Chunk.Content.Buffer[Chunk.Content.Buffer_Offset]!=0x00
         && (Chunk.Content.Buffer[Chunk.Content.Buffer_Offset]<'0'
          || Chunk.Content.Buffer[Chunk.Content.Buffer_Offset]>'9'))
    {
        IsOk=false;
        break;
    }
    Chunk.Content.Buffer_Offset=0;
    if (IsOk)
        Get_String(Chunk.Content.Size, Value);
    else
        for (Chunk.Content.Buffer_Offset=0; Chunk.Content.Buffer_Offset<Chunk.Content.Size; Chunk.Content.Buffer_Offset++)
            Value+=Ztring().From_CC1(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset);

    //Filling
    Global->Tdat->Strings["rn_o"]=Value;
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__Tdat_rn_O::Modify_Internal ()
{
    if (Global->Tdat->Strings["rn_o"].empty())
    {
        Chunk.Content.IsRemovable=true;
        return;
    }

    //Calculating size
    if (Global->Tdat->Strings["rn_o"].size()>=0xFFFFFFFF)
        return; //TODO: error

    //Creating buffer
    Chunk.Content.Buffer_Offset=0;
    Chunk.Content.Size=Global->Tdat->Strings["rn_o"].size();
    if (Chunk.Content.Size<40)
        Chunk.Content.Size=40;
    delete[] Chunk.Content.Buffer; Chunk.Content.Buffer=new int8u[Chunk.Content.Size];

    Put_String(Global->Tdat->Strings["rn_o"].size(), Global->Tdat->Strings["rn_o"]);
    memset(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset, 0x00, (size_t)(Chunk.Content.Size-Chunk.Content.Buffer_Offset));

    Chunk.Content.IsModified=true;
    Chunk.Content.Size_IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__Tdat_rn_O::Write_Internal ()
{
}
