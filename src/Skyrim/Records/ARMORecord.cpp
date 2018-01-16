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
#include "../../ModFile.h"
#include "ARMORecord.h"

namespace Sk
{
    ARMORecord::ARMORecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    ARMORecord::ARMORecord(ARMORecord *srcRecord) :
        TES5Record()
    {
        if (srcRecord == NULL)
            return;

        flags = srcRecord->flags;
        formID = srcRecord->formID;
        flagsUnk = srcRecord->flagsUnk;
        formVersion = srcRecord->formVersion;
        versionControl2[0] = srcRecord->versionControl2[0];
        versionControl2[1] = srcRecord->versionControl2[1];

        recData = srcRecord->recData;
        if (!srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        VMAD = srcRecord->VMAD;
        OBND = srcRecord->OBND;
        FULL = srcRecord->FULL;
        EITM = srcRecord->EITM;
        EAMT = srcRecord->EAMT;
        MOD2 = srcRecord->MOD2;
        MO2T = srcRecord->MO2T;
        MO2S = srcRecord->MO2S;
        ICON = srcRecord->ICON;
        MICO = srcRecord->MICO;
        MOD4 = srcRecord->MOD4;
        MO4T = srcRecord->MO4T;
        MO4S = srcRecord->MO4S;
        ICO2 = srcRecord->ICO2;
        MIC2 = srcRecord->MIC2;
        BODT = srcRecord->BODT;
        BOD2 = srcRecord->BOD2;
        DEST = srcRecord->DEST;
        YNAM = srcRecord->YNAM;
        ZNAM = srcRecord->ZNAM;
        ETYP = srcRecord->ETYP;
        BIDS = srcRecord->BIDS;
        BAMT = srcRecord->BAMT;
        RNAM = srcRecord->RNAM;
        KWDA = srcRecord->KWDA;
        DESC = srcRecord->DESC;
        MODL = srcRecord->MODL;
        DATA = srcRecord->DATA;
        DNAM = srcRecord->DNAM;
        TNAM = srcRecord->TNAM;

        if (!srcRecord->IsChanged())
            return;

        return;
    }

    ARMORecord::~ARMORecord()
    {
        //
    }

    uint32_t ARMORecord::GetType()
    {
        return REV32(ARMO);
    }

    char * ARMORecord::GetStrType()
    {
        return "ARMO";
    }


    bool ARMORecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;
        //TODO - implement VisitFormIDs for struct GENOBND

        if (EITM.IsLoaded()) {
            op.Accept(EITM.value);
        }
        if (DEST.IsLoaded()) {
            //TODO - implement VisitFormIDs for struct GENDESTRUCT
        }
        op.Accept(YNAM.value);
        op.Accept(ZNAM.value);
        if (ETYP.IsLoaded()) {
            op.Accept(ETYP.value);
        }
        if (BIDS.IsLoaded()) {
            op.Accept(BIDS.value);
        }
        if (BAMT.IsLoaded()) {
            op.Accept(BAMT.value);
        }
        op.Accept(RNAM.value);
        if (KWDA.IsLoaded()) {
            for (uint32_t i = 0; i < KWDA.value.size(); ++i) {

                op.Accept(KWDA.value[i]);

            };
        }
        if (MODL.IsLoaded()) {
            for (uint32_t i = 0; i < MODL.value.size(); ++i) {

                op.Accept(MODL.value[i]);

            };
        }
        if (DATA.IsLoaded()) {
            //TODO - implement VisitFormIDs for struct ARMODATA
        }
        if (TNAM.IsLoaded()) {
            op.Accept(TNAM.value);
        }

        return op.Stop();
    }


    int32_t ARMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
        while (buffer < end_buffer) {
            subType = *(uint32_t *)buffer;
            buffer += 4;
            switch (subType)
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
            switch (subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(VMAD):
                VMAD.Read(buffer, subSize, GetType(), CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize);
                break;
            case REV32(EAMT):
                EAMT.Read(buffer, subSize);
                break;
            case REV32(MOD2):
                MOD2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2T):
                MO2T.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2S):
                MO2S.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD4):
                MOD4.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4T):
                MO4T.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4S):
                MO4S.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MIC2):
                MIC2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BODT):
                BODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BOD2):
                BOD2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DEST):
                DEST.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize);
                break;
            case REV32(BIDS):
                BIDS.Read(buffer, subSize);
                break;
            case REV32(BAMT):
                BAMT.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(KSIZ):
                // Ignore on read
                buffer += subSize;
                break;
            case REV32(KWDA):
                KWDA.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(MODL):
                MODL.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;

            default:
                CBASH_SUBTYPE_UNKNOWN
                CBASH_CHUNK_DEBUG
                buffer = end_buffer;
                break;
            }
        };
        return 0;
    }

    int32_t ARMORecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        VMAD.Unload();
        OBND.Unload();
        FULL.Unload();
        EITM.Unload();
        EAMT.Unload();
        MOD2.Unload();
        MO2T.Unload();
        MO2S.Unload();
        ICON.Unload();
        MICO.Unload();
        MOD4.Unload();
        MO4T.Unload();
        MO4S.Unload();
        ICO2.Unload();
        MIC2.Unload();
        BODT.Unload();
        BOD2.Unload();
        DEST.Unload();
        YNAM.Unload();
        ZNAM.Unload();
        ETYP.Unload();
        BIDS.Unload();
        BAMT.Unload();
        RNAM.Unload();
        KWDA.Unload();
        DESC.Unload();
        MODL.Unload();
        DATA.Unload();
        DNAM.Unload();
        TNAM.Unload();

        return 1;
    }

    int32_t ARMORecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(OBND);
        WRITE(FULL);
        WRITE(EITM);
        WRITE(EAMT);
        WRITE(MOD2);
        WRITE(MO2T);
        WRITE(MO2S);
        WRITE(ICON);
        WRITE(MICO);
        WRITE(MOD4);
        WRITE(MO4T);
        WRITE(MO4S);
        WRITE(ICO2);
        WRITE(MIC2);
        WRITE(BODT);
        WRITE(BOD2);
        WRITE(DEST);
        WRITE(YNAM);
        WRITE(ZNAM);
        WRITE(ETYP);
        WRITE(BIDS);
        WRITE(BAMT);
        WRITE(RNAM);
        WRITE(KWDA);
        WRITE(DESC);
        WRITE(MODL);
        WRITE(DATA);
        WRITE(DNAM);
        WRITE(TNAM);
        return -1;
    }

    bool ARMORecord::operator ==(const ARMORecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            OBND == other.OBND &&
            FULL.equalsi(other.FULL) &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            MOD2.equalsi(other.MOD2) &&
            MO2T == other.MO2T &&
            MO2S == other.MO2S &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MOD4.equalsi(other.MOD4) &&
            MO4T == other.MO4T &&
            MO4S == other.MO4S &&
            ICO2.equalsi(other.ICO2) &&
            MIC2.equalsi(other.MIC2) &&
            BODT == other.BODT &&
            BOD2 == other.BOD2 &&
            DEST == other.DEST &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            ETYP == other.ETYP &&
            BIDS == other.BIDS &&
            BAMT == other.BAMT &&
            RNAM == other.RNAM &&
            KWDA == other.KWDA &&
            DESC.equalsi(other.DESC) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            TNAM == other.TNAM);
    }

    bool ARMORecord::operator !=(const ARMORecord &other) const
    {
        return !(*this == other);
    }

    bool ARMORecord::equals(Record *other)
    {
        return *this == *(ARMORecord *)other;
    }
}