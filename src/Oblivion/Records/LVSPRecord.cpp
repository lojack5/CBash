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
#include "LVSPRecord.h"

namespace Ob
{
LVSPRecord::LVSPRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LVSPRecord::LVSPRecord(LVSPRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    LVLD = srcRecord->LVLD;
    LVLF = srcRecord->LVLF;
    Entries = srcRecord->Entries;
    return;
    }

LVSPRecord::~LVSPRecord()
    {
    //
    }

bool LVSPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < Entries.value.size(); ListIndex++)
        op.Accept(Entries.value[ListIndex]->listId);

    return op.Stop();
    }

bool LVSPRecord::IsCalcFromAllLevels()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcFromAllLevels) != 0 : false;
    }

void LVSPRecord::IsCalcFromAllLevels(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcFromAllLevels) : (*LVLF.value & ~fCalcFromAllLevels);
    }

bool LVSPRecord::IsCalcForEachItem()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcForEachItem) != 0 : false;
    }

void LVSPRecord::IsCalcForEachItem(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcForEachItem) : (*LVLF.value & ~fCalcForEachItem);
    }

bool LVSPRecord::IsUseAllSpells()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fUseAllSpells) != 0 : false;
    }

void LVSPRecord::IsUseAllSpells(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fUseAllSpells) : (*LVLF.value & ~fUseAllSpells);
    }

bool LVSPRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    LVLF.Load();
    return Exact ? ((*LVLF.value & Mask) == Mask) : ((*LVLF.value & Mask) != 0);
    }

void LVSPRecord::SetFlagMask(uint8_t Mask)
    {
    LVLF.Load();
    *LVLF.value = Mask;
    }

uint32_t LVSPRecord::GetType()
    {
    return REV32(LVSP);
    }

char * LVSPRecord::GetStrType()
    {
    return "LVSP";
    }

int32_t LVSPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(LVLD):
                LVLD.Read(buffer, subSize);
                if((LVLD.value & fAltCalcFromAllLevels) != 0)
                    {
                    LVLD.value &= ~fAltCalcFromAllLevels;
                    IsCalcFromAllLevels(true);
                    }
                break;
            case REV32(LVLF):
                LVLF.Read(buffer, subSize);
                break;
            case REV32(LVLO):
                Entries.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LVSP: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %08x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t LVSPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    LVLD.Unload();
    LVLF.Unload();
    Entries.Unload();
    return 1;
    }

int32_t LVSPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(LVLD);
    WRITE(LVLF);
    WRITEAS(Entries,LVLO);
    return -1;
    }

bool LVSPRecord::operator ==(const LVSPRecord &other) const
    {
    return (LVLD == other.LVLD &&
            LVLF == other.LVLF &&
            EDID.equalsi(other.EDID) &&
            Entries == other.Entries);
    }

bool LVSPRecord::operator !=(const LVSPRecord &other) const
    {
    return !(*this == other);
    }

bool LVSPRecord::equals(Record *other)
    {
    return *this == *(LVSPRecord *)other;
    }
}