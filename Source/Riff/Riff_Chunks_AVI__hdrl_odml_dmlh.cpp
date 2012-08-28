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
void Riff_AVI__hdrl_odml_dmlh::Read_Internal ()
{
    //Integrity
    if (Global->AVI__hdrl_dmlh)
        throw exception_valid("2 dmlh chunks");
    if (Global->AVI__hdrl_avih==NULL)
        throw exception_valid("avih chunk is missing");

    //Filling
    Global->AVI__hdrl_dmlh=new Riff_Base::global::chunk_AVI__hdrl_dmlh;
    
    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    Get_L4 (Global->AVI__hdrl_avih->TotalFrames);
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_odml_dmlh::Modify_Internal ()
{
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_odml_dmlh::Write_Internal ()
{
}


