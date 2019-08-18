/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "../../Common.h"
#include "NOTERecord.h"

namespace FNV
{
NOTERecord::NOTERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NOTERecord::NOTERecord(NOTERecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    DATA = srcRecord->DATA;
    ONAM = srcRecord->ONAM;
    XNAM = srcRecord->XNAM;
    TNAM = srcRecord->TNAM;
    TNAMAlt = srcRecord->TNAMAlt;
    SNAM = srcRecord->SNAM;
    return;
    }

NOTERecord::~NOTERecord()
    {
    //
    }

bool NOTERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(uint32_t x = 0; x < ONAM.value.size(); x++)
        op.Accept(ONAM.value[x]);

    if(IsVoice() && TNAMAlt.IsLoaded())
        op.Accept(TNAMAlt.value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);

    return op.Stop();
    }

bool NOTERecord::IsSound()
    {
    return DATA.value == eSound;
    }

void NOTERecord::IsSound(bool value)
    {
    DATA.value = value ? eSound : eText;
    }

bool NOTERecord::IsText()
    {
    return DATA.value == eText;
    }

void NOTERecord::IsText(bool value)
    {
    DATA.value = value ? eText : eSound;
    }

bool NOTERecord::IsImage()
    {
    return DATA.value == eImage;
    }

void NOTERecord::IsImage(bool value)
    {
    DATA.value = value ? eImage : eSound;
    }

bool NOTERecord::IsVoice()
    {
    return DATA.value == eVoice;
    }

void NOTERecord::IsVoice(bool value)
    {
    DATA.value = value ? eVoice : eSound;
    }

bool NOTERecord::IsType(uint8_t Type)
    {
    return DATA.value == Type;
    }

void NOTERecord::SetType(uint8_t Type)
    {
    DATA.value = Type;
    }

uint32_t NOTERecord::GetType()
    {
    return REV32(NOTE);
    }

char * NOTERecord::GetStrType()
    {
    return "NOTE";
    }

int32_t NOTERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TNAM):
                if(IsVoice())
                    TNAMAlt.Read(buffer, subSize);
                else
                    TNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NOTE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %08x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t NOTERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    DATA.Unload();
    ONAM.Unload();
    XNAM.Unload();
    TNAM.Unload();
    TNAMAlt.Unload();
    SNAM.Unload();
    return 1;
    }

int32_t NOTERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(DATA);
    WRITE(ONAM);
    WRITE(XNAM);
    if(IsVoice())
        WRITEAS(TNAMAlt,TNAM);
    else
        WRITE(TNAM);
    WRITE(SNAM);
    return -1;
    }

bool NOTERecord::operator ==(const NOTERecord &other) const
    {
    return (OBND == other.OBND &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            DATA == other.DATA &&
            SNAM == other.SNAM &&
            TNAMAlt == other.TNAMAlt &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            XNAM.equalsi(other.XNAM) &&
            TNAM.equalsi(other.TNAM) &&
            MODL == other.MODL &&
            ONAM == other.ONAM);
    }

bool NOTERecord::operator !=(const NOTERecord &other) const
    {
    return !(*this == other);
    }

bool NOTERecord::equals(Record *other)
    {
    return *this == *(NOTERecord *)other;
    }
}