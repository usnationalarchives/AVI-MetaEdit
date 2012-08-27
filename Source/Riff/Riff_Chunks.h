// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef Riff_ChunksH
#define Riff_ChunksH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Riff/Riff_Base.h"
//---------------------------------------------------------------------------

//***************************************************************************
// 
//***************************************************************************

class Riff : public Riff_Base
{
public:
    //Constructor/Destructor
    Riff();
    ~Riff();

protected:
    //Read/Write
    void    Read_Internal       ();
    void    Insert_Internal     (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos); 
};

//***************************************************************************
// Constants
//***************************************************************************

namespace Elements
{
    const int32u LIST=0x4C495354;
    const int32u RIFF=0x52494646;

    const int32u AVI_=0x41564920;
    const int32u AVI___PMX=0x5F504D58;
    const int32u AVI__aXML=0x61584D4C;
    const int32u AVI__fact=0x66616374;
    const int32u AVI__filr=0x66696C72;
    const int32u AVI__FILR=0x46494C52;
    const int32u AVI__fllr=0x666C6C72;
    const int32u AVI__FLLR=0x464C4C52;
    const int32u AVI__hdrl=0x6864726C;
    const int32u AVI__hdrl_avih=0x61766968;
    const int32u AVI__hdrl_odml=0x6F646D6C;
    const int32u AVI__hdrl_odml_dmlh=0x646D6C68;
    const int32u AVI__hdrl_strl=0x7374726C;
    const int32u AVI__hdrl_strl_indx=0x696E6478;
    const int32u AVI__hdrl_strl_strf=0x73747266;
    const int32u AVI__hdrl_strl_strh=0x73747268;
    const int32u AVI__hdlr_strl_strh_auds=0x61756473;
    const int32u AVI__hdlr_strl_strh_iavs=0x69617673;
    const int32u AVI__hdlr_strl_strh_mids=0x6D696473;
    const int32u AVI__hdlr_strl_strh_vids=0x76696473;
    const int32u AVI__hdlr_strl_strh_txts=0x74787473;
    const int32u AVI__ID3_=0x49443320;
    const int32u AVI__idx1=0x69647831;
    const int32u AVI__INFO=0x494E464F;
    const int32u AVI__INFO_IDIT=0x49444954;
    const int32u AVI__INFO_xxxx=0xFFFFFFFF;
    const int32u AVI__iXML=0x69584D4C;
    const int32u AVI__junk=0x6A756E6B;
    const int32u AVI__JUNK=0x4A554E4B;
    const int32u AVI__junq=0x6A756E71;
    const int32u AVI__JUNQ=0x4A554E51;
    const int32u AVI__MD5_=0x4D443520;
    const int32u AVI__movi=0x6D6F7669;
    const int32u AVI__movi___db=0x00006462;
    const int32u AVI__movi___dc=0x00006463;
    const int32u AVI__movi___ix=0x00006978;
    const int32u AVI__movi___pc=0x00007063;
    const int32u AVI__movi___wb=0x00007762;
    const int32u AVI__movi_ix__=0x69780000;
    const int32u AVI__movi_xxxx=0x00000000;
    const int32u AVI__pad_=0x70616420;
    const int32u AVI__PAD_=0x50414420;
    const int32u AVI__Tdat=0x54646174;
    const int32u AVI__Tdat_rn_A=0x726E5F41;
    const int32u AVI__Tdat_rn_O=0x726E5F4F;
    const int32u AVI__Tdat_tc_A=0x74635F41;
    const int32u AVI__Tdat_tc_O=0x74635F4F;
    const int32u AVIX=0x41564958;
    const int32u AVIX_movi=0x6D6F7669;
}

//***************************************************************************
// List of chunks
//***************************************************************************

//Chunk without modification
#define CHUNK__(_Level, _Name) \
class Riff_##_Name : public Riff_Base \
{ \
public: \
    Riff_##_Name(global* Global):Riff_Base(Global, _Level) {Chunk.Header.Name=Elements::_Name;} \
protected: \
    void Read_Internal(); \
}; \

//Chunk with insertion
#define CHUNK_I(_Name) \
class Riff_##_Name : public Riff_Base \
{ \
public: \
    Riff_##_Name(Riff_Base* Parent_):Riff_Base(Parent_) {Chunk.Header.IsList=true; Chunk.Header.Name=Elements::_Name;} \
protected: \
    void    Read_Internal       (); \
    void    Seek_Internal       (); \
    void    Insert_Internal     (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos); \
}; \

//Chunk with modification/write
#define CHUNK_W(_Name) \
class Riff_##_Name : public Riff_Base \
{ \
public: \
    Riff_##_Name(Riff_Base* Parent_):Riff_Base(Parent_) {Chunk.Header.Name=Elements::_Name;} \
protected: \
    void Read_Internal(); \
    void Modify_Internal(); \
    void Write_Internal(); \
}; \

CHUNK_I(AVI_);
CHUNK_W(AVI___PMX);
CHUNK_W(AVI__aXML);
CHUNK_I(AVI__hdrl);
CHUNK_W(AVI__hdrl_avih);
CHUNK_I(AVI__hdrl_odml);
CHUNK_W(AVI__hdrl_odml_dmlh);
CHUNK_I(AVI__hdrl_strl);
CHUNK_W(AVI__hdrl_strl_indx);
CHUNK_W(AVI__hdrl_strl_strf);
CHUNK_W(AVI__hdrl_strl_strh);
CHUNK_I(AVI__INFO);
CHUNK_W(AVI__INFO_xxxx);
CHUNK_W(AVI__idx1);
CHUNK_W(AVI__iXML);
CHUNK_W(AVI__JUNK);
CHUNK_W(AVI__MD5_);
CHUNK_I(AVI__movi);
CHUNK_W(AVI__movi___ix);
CHUNK_W(AVI__movi_xxxx);
CHUNK_I(AVI__Tdat);
CHUNK_W(AVI__Tdat_rn_A);
CHUNK_W(AVI__Tdat_rn_O);
CHUNK_W(AVI__Tdat_tc_A);
CHUNK_W(AVI__Tdat_tc_O);
CHUNK_I(AVIX);

#endif
