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
#include "FURNRecord.h"

namespace Sk
{
    FURNRecord::FURNRecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    FURNRecord::FURNRecord(FURNRecord *srcRecord) :
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
        MODL = srcRecord->MODL;
        DEST = srcRecord->DEST;
        KWDA = srcRecord->KWDA;
        PNAM = srcRecord->PNAM;
        FNAM = srcRecord->FNAM;
        KNAM = srcRecord->KNAM;
        MNAM = srcRecord->MNAM;
        WBDT = srcRecord->WBDT;
        XMRK = srcRecord->XMRK;
        NAM1 = srcRecord->NAM1;
        ENAM = srcRecord->ENAM;
        NAM0 = srcRecord->NAM0;
        FNMK = srcRecord->FNMK;
        FNPR = srcRecord->FNPR;

        return;
    }

    FURNRecord::~FURNRecord()
    {
        //
    }

    uint32_t FURNRecord::GetType()
    {
        return REV32(FURN);
    }

    char * FURNRecord::GetStrType()
    {
        return "FURN";
    }


    bool FURNRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;
        //TODO - implement VisitFormIDs for struct GENOBND

        if (DEST.IsLoaded()) {
            //TODO - implement VisitFormIDs for struct GENDESTRUCT
        }
        if (KWDA.IsLoaded()) {
            for (uint32_t i = 0; i < KWDA.value.size(); ++i) {

                op.Accept(KWDA.value[i]);

            };
        }

        for (uint32_t x = 0; x < ENAM.value.size(); ++x)
            op.Accept(ENAM.value[x]);
        for (uint32_t x = 0; x < NAM0.value.size(); ++x)
            op.Accept(NAM0.value[x]);
        for (uint32_t x = 0; x < FNPR.value.size(); ++x)
            op.Accept(FNPR.value[x]);

        return op.Stop();
    }


    int32_t FURNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODL):
                MODL.MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODT):
                MODL.MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DEST):
                DEST.Read(buffer, subSize);
                break;
            case REV32(KSIZ):
                // Ignore on read
                buffer += subSize;
                break;
            case REV32(KWDA):
                KWDA.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(KNAM):
                KNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(WBDT):
                WBDT.Read(buffer, subSize);
                break;
            case REV32(XMRK):
                XMRK.MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize);
                break;
            case REV32(FNMK):
                FNMK.Read(buffer, subSize);
                break;
            case REV32(FNPR):
                FNPR.Read(buffer, subSize);
                break;
            case REV32(MODS):
            case REV32(DSTD):
            case REV32(DSTF):
                CBASH_SUBTYPE_NOT_IMPLEMENTED
                buffer += subSize;
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

    int32_t FURNRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        VMAD.Unload();
        OBND.Unload();
        FULL.Unload();
        DEST.Unload();
        KWDA.Unload();
        PNAM.Unload();
        FNAM.Unload();
        KNAM.Unload();
        MNAM.Unload();
        WBDT.Unload();
        NAM1.Unload();
        ENAM.Unload();
        NAM0.Unload();
        FNMK.Unload();
        FNPR.Unload();

        return 1;
    }

    int32_t FURNRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(OBND);
        WRITE(FULL);
        MODL.Write(writer);
        WRITE(DEST);
        WRITE(KWDA);
        WRITE(PNAM);
        WRITE(FNAM);
        WRITE(KNAM);
        WRITE(MNAM);
        WRITE(WBDT);
        XMRK.Write(writer);
        WRITE(NAM1);
        WRITE(ENAM);
        WRITE(NAM0);
        WRITE(FNMK);
        WRITE(FNPR);

        return -1;
    }

    bool FURNRecord::operator ==(const FURNRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            OBND == other.OBND &&
            FULL.equalsi(other.FULL) &&
            MODL == other.MODL &&
            DEST == other.DEST &&
            KWDA == other.KWDA &&
            PNAM == other.PNAM &&
            FNAM == other.FNAM &&
            KNAM == other.KNAM &&
            MNAM == other.MNAM &&
            WBDT == other.WBDT &&
            XMRK == other.XMRK &&
            NAM1 == other.NAM1 &&
            ENAM == other.ENAM &&
            NAM0 == other.NAM0 &&
            FNMK == other.FNMK &&
            FNPR == other.FNPR);
    }

    bool FURNRecord::operator !=(const FURNRecord &other) const
    {
        return !(*this == other);
    }

    bool FURNRecord::equals(Record *other)
    {
        return *this == *(FURNRecord *)other;
    }
}