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
void Riff_AVI__hdrl_strl_strh::Read_Internal ()
{
    if (Global->AVI__hdrl_strl_strh.size()!=Global->AVI__hdrl_strl_strf.size())
        throw exception_read_chunk("Coherency problem during strl parsing");
    
    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    global::chunk_AVI__hdrl_strl_strh* Temp=new global::chunk_AVI__hdrl_strl_strh();
    Get_C4 (Temp->fccType);
    Skip_XX(4*4);
    Get_L4 (Temp->Scale);
    Get_L4 (Temp->Rate);

    //Filling
    Global->AVI__hdrl_strl_strh.push_back(Temp);
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_strh::Modify_Internal ()
{
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_strh::Write_Internal ()
{
}


