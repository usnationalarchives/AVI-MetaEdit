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
void Riff_AVI__hdrl_strl_strf::Read_Internal ()
{
    if (Global->AVI__hdrl_strl_strh.size()!=Global->AVI__hdrl_strl_strf.size()+1)
        throw exception_read_chunk("Coherency problem during strl parsing");
    
    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    global::chunk_AVI__hdrl_strl_strf* Temp=new global::chunk_AVI__hdrl_strl_strf();
    switch (Global->AVI__hdrl_strl_strh[Global->AVI__hdrl_strl_strh.size()-1]->fccType)
    {
        case Elements::AVI__hdlr_strl_strh_auds :
                                                    Get_L2 (Temp->FormatTag);
                                                    Get_L2 (Temp->Channels);
                                                    Get_L4 (Temp->SamplesPerSec);
                                                    Get_L4 (Temp->AvgBytesPerSec);
                                                    Skip_XX(2); //BlockAlign
                                                    Get_L2 (Temp->BitsPerSample);
                                                    break;

        //case Elements::AVI__hdlr_strl_strh_iavs : AVI__hdlr_strl_strf_iavs(); break;
        //case Elements::AVI__hdlr_strl_strh_mids : AVI__hdlr_strl_strf_mids(); break;
        //case Elements::AVI__hdlr_strl_strh_txts : AVI__hdlr_strl_strf_txts(); break;
        case Elements::AVI__hdlr_strl_strh_vids : 
                                                    Skip_XX(1*4);
                                                    Get_L4 (Temp->Width);
                                                    Get_L4 (Temp->Height);
                                                    Skip_XX(2); //Planes
                                                    Get_L2 (Temp->BitCount);
                                                    Get_C4 (Temp->Compression);
                                                    Get_L4 (Temp->SizeImage);
                                                    break;
        default                                 : ;
    }

    //Filling
    Global->AVI__hdrl_strl_strf.push_back(Temp);
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_strf::Modify_Internal ()
{
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_strl_strf::Write_Internal ()
{
}


