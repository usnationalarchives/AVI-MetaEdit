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
void Riff_AVI__hdrl_avih::Read_Internal ()
{
    //Integrity
    if (Global->AVI__hdrl_avih)
        throw exception_valid("2 avih chunks");
    
    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    global::chunk_AVI__hdrl_avih* Temp=new global::chunk_AVI__hdrl_avih();
    Get_L4 (Temp->MicrossecPerFrame);
    Skip_XX(3*4);
    Get_L4 (Temp->TotalFrames);

    //Filling
    Global->AVI__hdrl_avih=Temp;
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_avih::Modify_Internal ()
{
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_avih::Write_Internal ()
{
}


