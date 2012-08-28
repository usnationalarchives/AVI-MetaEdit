// AVI MetaEdit Common - Common stuff for AVI MetaEdit interfaces
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Common/Common_About.h"
//---------------------------------------------------------------------------

//***************************************************************************
// NameVersion
//***************************************************************************

//---------------------------------------------------------------------------
const char* NameVersion_HTML() {return
    "<a href=\"http://www.archives.gov/preservation/products/\">U.S. National Archives</a> AVI MetaEdit 1.0.0"
;}

//---------------------------------------------------------------------------
const char* NameVersion_Text() {return
"U.S. National Archives\n"
"AVI MetaEdit 1.0.0"
;}

//***************************************************************************
// NameVersion
//***************************************************************************

//---------------------------------------------------------------------------
const char* Description_HTML() {return
"<h3>DESCRIPTION</h3>"
""
"AVI MetaEdit was developed by the U.S. National Archives supported by AudioVisual Preservation Solutions.<br />"
"<br />"
"This tool permits embedding, editing, and exporting of metadata in AVI (Standard and OpenDML) files. This tool can also enforce metadata guidelines developed by the <a href=\"http://www.archives.gov/preservation/products/\">U.S. National Archives</a>, as well as format specifications from Microsoft and IBM."
;}

//---------------------------------------------------------------------------
const char* Description_Text() {return
"DESCRIPTION\n"
"\n"
"AVI MetaEdit was developed by U.S. National Archives\n"
"supported by AudioVisual Preservation Solutions.\n"
"\n"
"This tool permits embedding, editing, and exporting of metadata in\n" 
"AVI (Standard or OpenDML) files. This tool can also enforce metadata\n" 
"guidelines developed by the U.S. National Archives,\n"
"as well as format specifications from Microsoft and IBM.\n"
"\n"
;}

//***************************************************************************
// AuthorLicense
//***************************************************************************

//---------------------------------------------------------------------------
const char* AuthorLicense_HTML() {return
"" //now in /Source/Ressource/License.html
;}

//---------------------------------------------------------------------------
const char* AuthorLicense_Text() {return
"AUTHOR and LICENSE\n"
"\n"
"This code was created in 2011 for U.S. National Archives\n"
"and its license is NARA OPEN SOURCE AGREEMENT VERSION 1.3.\n"
;}

//***************************************************************************
// Contact
//***************************************************************************

//---------------------------------------------------------------------------
const char* Contact_HTML() {return
"<h3>CONTACT</h3>"
""
"Please submit questions, comments or feedback to <a href=\"http://www.archives.gov/preservation/products/\">U.S. National Archives</a>."
;}

//---------------------------------------------------------------------------
const char* Contact_Text() {return
"CONTACT\n"
"\n"
"Please submit questions, comments or feedback to\n"
"http://www.archives.gov/preservation/products/ .\n"
"\n"
;}

//***************************************************************************
// Websites
//***************************************************************************

//---------------------------------------------------------------------------
const char* Websites_HTML() {return
"Developed with support from <a href=\"http://avpreserve.com\">AVPS</a> and <a href=\"http://mediaarea.net\">MediaArea.net</a>"
;}

//---------------------------------------------------------------------------
const char* Websites_Text() {return
"Developed with support from http://avpreserve.com and http://mediaarea.net"
"\n"
;}

//***************************************************************************
// Columns
//***************************************************************************

struct column_text
{
    const char* Name;
    const char* ToolTip;
};
const size_t Columns_Text_Size=25+4+20;
column_text Columns[]=
{
    //{"FileName", "In order to provide a concise presentation the filepaths are displayed from the directory path where the files diverge. Thus if two files are opened from /HardDrive1/videofiles/movies/videofile.avi and /HardDrive1/videofiles/spokenword/videofileB.avi then these will be displayed in the table view as /movies/videofile.avi and /spokenword/videofileB.avi since the /HardDrive1/videofiles section of the Filepath is common to the open files."},
    {"FileSize", "The size of the video file in bytes."},
    {"Format", "This value represents the type of container utilized by the file, including profile information."},
    {"Duration", "The total playing time, displayed in HH:MM:SS.mmm (hours, minutes, seconds, milliseconds)"},
    {"Vid Format", "The name of the codec used to encode the video data."},
    {"Vid CodecID", "The four character code (fourCC) used by the AVI container to describe the video codec."},
    {"Vid FrameRate", "The amount of frames per second intended for presentation on playback of the file."},
    {"Vid Width", "The number of pixel columns within the frames of the video stream."},
    {"Vid Height", "The number of pixel rows within the frames of the video stream."},
    {"Vid BitDepth", "The number of bits of data per channel per pixel that the video data will decode to."},
    {"Vid BitRate", "A measurement in bits per second for the video stream."},
    {"Aud Format", "The two character code (twoCC) used by the AVI container to describe the audio codec."},
    {"Aud CodecID", "This value represents the type of compression utilized within the audio data."},
    {"Aud Channels", "The number of audio channels encoded within the audio stream."},
    {"Aud SampleRate", "The number of audio samples per second."},
    {"Aud BitRate", "The number of bits utilized per second of audio."},
    {"Aud BitDepth", "The number of bits of data per channel per sample that the audio data will decode to."},
    {"UnprocessedChunks", "Unprocessed chunks"},
    {"Tdat", "Notes the existance of the Tdat chunk.."},
    {"INFO", "Notes the existence of the INFO chunk."},
    {"XMP", "Notes the existence of the XMP chunk."},
    {"aXML", "Notes the existence of the aXML chunk."},
    {"iXML", "Notes the existence of the iXML chunk."},
    {"MD5Stored", "If an MD5 chunk exists, this column will show the stored value. This MD5 value is a checksum of the video and audio data only (starting after the chunk identifier and size) and does not include the file's metadata or any other chunk."},
    {"MD5Generated", "If the MD5 is generated it will appear in this column. Any conflict between this column and the 'MD5' column indicates a change in the video or audio data portion of the file between the current evaluation and the stored evaluation."},
    {"Errors", "Provides statements about potential structural problems with a given audio files: for instance if the RIFF size statement conflicts with the actual file size or if the audio files does not utilize padding bytes to follow odd byte length chunks."},
    {"Information", "Used for status notes and technical information during operation."},

    {"tc_A", ""},
    {"tc_O", ""},
    {"rn_A", ""},
    {"rn_O", ""},
    {"IARL", "Archival Location\nIndicates where the subject of the file is archived.\n\nU.S. National Archives Application:\nThis element is an approximate equivalent to the Originator element in the BEXT chunk which records the entity responsible for the 'archiving' (creation, maintenance, preservation) of this digital item.\nIf used, this element could repeat the data from the Originator element in the same structured format.\nIn some applications, it is automatically carried over to the MP3 ID3 element 'ArchivalLocation'.\nOf all the info list chunk elements, this is the most important for Federal Agencies because it is vital to document the archival responsibility for a content item.\nEntity designations should be as specific as possible including a two-character county code to avoid the potential for conflict in the archiving entity's name.\nThe archival entity should be identified at the most specific level within the institution.\n\nU.S. National Archives Requirement:\nStrongly recommended ('required') if using LIST-INFO chunk.\n\nU.S. National Archives Formatting:\nTwo capital letters which must be derived from ISO 3166 Country Codes,\nOne comma,\nOne space,\nInstitutional Acronym.\nAlmost always one word all caps but there are some acronyms that are more than one word. The resource GovSpeak: A Guide to Government Acronyms and Abbreviations is suggested as a source but not required.\nThis string should be identical to what is in the Originator data space.\nIf any fields in LIST-INFO are used, this data should automatically carry over from Originator.\n\nU.S. National Archives Examples:\n US, NARA\n US, LOC/RSS"},
    {"IART", "Artist\nLists the artist of the original subject of the file. For example, Michaelangelo."},
    {"ICMS", "Commissioned\nLists the name of the person or organization that commissioned the subject of the file. For example, Pope Julian II."},
    {"ICMT", "Comment\nProvides general comments about the file or the subject of the file. If the comment is several sentences long, end each sentence with a period. Do not include newline characters.\n\nU.S. National Archives Application:\nIf used, this element should repeat the principal and other identifiers from the OriginatorReference and/or Description element in the BEXT chunk.\nEach identifier will be labeled as to its origin or purpose using the 'type' and 'comment' qualifiers.\nUsing the tag 'local' in the 'type' qualifier implies the entity identified in the BEXT Originator element.\nIn some applications, this info list element may carry forward automatically to the MP3 ID3 tagged element 'Comment'.\nNote: The Working Group perceived value in the practices of labeling identifiers (see examples) but wished to leave this as an optional practice.\n\nU.S. National Archives Requirement:\nOptional\n\nU.S. National Archives Formatting:\nIf labeled: Identifier [comma space] type [comma space] comment [semicolon-space if more than one identifier]\nIf no labeling: Identifier\n\nU.S. National Archives Examples:\nNARA: 58979818, local, principal ID original filename\nNARA: 306-MUSA-9658B, local, RG-Series-Item Number\nLC: 1201566-2-1, local, system-generated number; RYI 6039, local, source location number\nLC: http://hdl.loc.gov/loc.mbrsmi/westhpp.2033, URL, principal ID Handle\nDigital Library: ark.cdlib.org.org/ark:/13030/tf5p30086k, URL, ARK\nLC: http://lccn.loc.gov/mp76000002"},
    {"ICOP", "Copyright\nRecords the copyright information for the file. For example, Copyright Encyclopedia International 1991. If there are multiple copyrights, separate them by a semicolon followed by a space.\n\nU.S. National Archives Application:\nInformation about copyright and other restrictions (donor, privacy, etc.).\nUsage by federal agencies will often refer to the documentation of restrictions provided by other, non- embedded metadata.\nThis element has no equivalent in the BEXT chunk.\nIn some applications, this info list element may carry forward automatically to MP3 ID3 tagged element \"Copyright.\"\n\nIf used, this element may contain the information as known at the time of embedding.\nThe Working Group understands that metadata may be updated over time.\nUsers who refer to an embedded block of metadata should understand that this may not represent the latest and best information,\nand they should be counseled to follow one of the identifiers in order to obtain later and/or better data.\n\nU.S. National Archives Requirement:\nOptional\n\nU.S. National Archives Examples:\n LC: Publication and other forms of distribution may be restricted. For details, contact the Recorded Sound Section of the Library of Congress. [Preferred wording from LC, RSS]\nLC: (p) Rhino Records 2002.\nLC: 1201566-2-1, local, system-generated number; RYI 6039, local, source location number\nLC<: See Copyright Restriction Statement. [Used by LC, American Folklife Center]"},
    {"ICRD", "Creation date\nSpecifies the date the subject of the file was created. List dates in year-month-day format, padding one-digit months and days with a zero on the left. For example: 1553-05-03 for May 3, 1553.\nThe year should always be given using four digits.\n\nU.S. National Archives Application: This element is an equivalent to the OriginationDate in the BEXT chunk.\nIf used, this element could repeat the information from the OriginationDate element in the BEXT chunk using the same structured format.\nIn some applications, this info list element may carry forward automatically to MP3 ID3 tagged element \"CreationDate.\"\n\nU.S. National Archives Requirement:\nOptional.\n\nU.S. National Archives Example:\n2005-11-30"},
    {"IENG", "Engineer\nStores the name of the engineer who worked on the file. If there are multiple engineers, separate the names by a semicolon and a blank.\n\nU.S. National Archives example:\nSmith, John; Adams, Joe."},
    {"IGNR", "Genre\nDescribes the original work, such as jazz, classical, rock, etc."},
    {"IKEY", "Keywords\nProvides a list of keywords that refer to the file or subject of the file. Separate multiple keywords with a semicolon and a blank.\n\nU.S. National Archives example:\n Seattle; zoology; The Civil War."},
    {"IMED", "Medium\nDescribes the original subject of the file, such as record, CD and so forth."},
    {"INAM", "Name (Title)\nStores the title of the subject of the file, such as Seattle From Above.\n\nU.S. National Archives Application:\nIf used, this element should contain a working title.\nThis phrase is intended to convey the Working Group's understanding that metadata may be updated over time.\nUsers who refer to elements like titles in an embedded block of metadata should understand that this may not represent the latest and best information,\nand they should be counseled to follow one of the identifiers in order to obtain later and/or better data.\n\nU.S. National Archives Requirement:\nOptional.\n\nU.S. National Archives Examples:\nLC: Symphony no. 3 in A minor, op. 56\nLC: Interview with Bo Dollis at WWOZ, New Orleans, 1999-03-24 [title assigned by cataloger]\nLC: Adventures in research. No. 587, Sawing off Manhattan Island [episode in a radio series]"},
    {"IPRD", "Product (Album)\nSpecifies the name of the title the file was originally intended for, such as The Civil War: The Musical."},
    {"ISBJ", "Subject\nDescribes the contents of the file, such as Metadata Management."},
    {"ISFT", "Software\nIdentifies the name of the software package used to create the file, such as Audacity 1.3.9."},
    {"ISRC", "Source\nIdentifies the name of the person or organization who supplied the original subject of the file. For example: NARA."},
    {"ISRF", "Source Form\nIdentifies the original form of the material that was digitized, such as record, sampling CD, TV sound track and so forth. This is not necessarily the same as IMED."},
    {"ITCH", "Technician\nIdentifies the technician who sampled the subject file.\nFor example: Smith, John."},
    {"ISMP", "SMPTE time code of digitization start point expressed as a NULL terminated text string \"HH:MM:SS.FF\""},
    {"IDIT", "Specifies the time and date that digitization commenced.\nThe digitization time is contained in an ASCII string which contains exactly 26 characters and is in the format \"Wed Jan 02 02:03:55 1990\"."},
    {"IMIT", "More Info Text"},
};

//---------------------------------------------------------------------------
const char* Columns_ToolTip(std::string Name)
{
    for (size_t Pos=0; Pos<Columns_Text_Size; Pos++)
        if (Name==Columns[Pos].Name)
            return Columns[Pos].ToolTip; 
    return ""; //no info
}

