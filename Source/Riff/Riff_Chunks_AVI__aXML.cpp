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
// AVI_ aXML
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__aXML::Read_Internal ()
{
    //Integrity
    if (Global->aXML)
        throw exception_valid("2 aXML chunks");

    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Filling
    Global->aXML=new Riff_Base::global::chunk_strings;
    Get_String(Chunk.Content.Size, Global->aXML->Strings["axml"]);
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__aXML::Modify_Internal ()
{
    if (Global->aXML==NULL
     || Global->aXML->Strings["axml"].empty())
    {
        Chunk.Content.IsRemovable=true;
        return;
    }

    //Calculating size
    const string &Value=Global->aXML->Strings["axml"];
    if (Value.size()>=0xFFFFFFFF)
        return; //TODO: error

    //Creating buffer
    Chunk.Content.Buffer_Offset=0;
    Chunk.Content.Size=Value.size();
    delete[] Chunk.Content.Buffer; Chunk.Content.Buffer=new int8u[Value.size()];

    Put_String(Value.size(), Value);

    Chunk.Content.IsModified=true;
    Chunk.Content.Size_IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__aXML::Write_Internal ()
{
}

