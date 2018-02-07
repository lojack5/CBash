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
#include "SPELRecord.h"

namespace Sk
{
    SPELRecord::SPELRecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }
    
    SPELRecord::SPELRecord(SPELRecord *srcRecord) :
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
        if(!srcRecord->IsChanged())
            return;
        EDID = srcRecord->EDID;
        OBND = srcRecord->OBND;
        FULL = srcRecord->FULL;
        DESC = srcRecord->DESC;
        MDOB = srcRecord->MDOB;
        ETYP = srcRecord->ETYP;
        SPIT = srcRecord->SPIT;
        effects = srcRecord->effects;

        return;
    }

    SPELRecord::~SPELRecord()
    {
        //
    }

    uint32_t SPELRecord::GetType()
    {
        return REV32(SPEL);
    }

    char * SPELRecord::GetStrType()
    {
        return "SPEL";
    }


    bool SPELRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;
        //TODO - implement VisitFormIDs for struct GENOBND

        if (MDOB.IsLoaded()) {
            op.Accept(MDOB.value);
        }
        op.Accept(ETYP.value);

        return op.Stop();
    }


    int32_t SPELRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
        
        SpellEffect *currentEffect = NULL;
        
        while (buffer < end_buffer){
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(MDOB):
                MDOB.Read(buffer, subSize);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                break;
            case REV32(SPIT):
                SPIT.Read(buffer, subSize);
                break;
            case REV32(EFID):
                currentEffect = new SpellEffect();
                effects.value.push_back(currentEffect);
                currentEffect->EFID.Read(buffer, subSize);
                break;
                
            case REV32(EFIT):
                if(currentEffect != NULL) {
                    currentEffect->EFIT.Read(buffer, subSize);
                } else {
                    printer("  SPEL: %08X - EFIT found without an effect initialized\n", formID);
                    buffer += subSize;
                } 
                
                break;

            case REV32(CTDA):
                if(currentEffect != NULL) {
                    currentEffect->CTDA.Read(buffer, subSize);
                } else {
                    printer("  SPEL: %08X - CTDA found without an effect initialized\n", formID);
                    buffer += subSize;
                } 
            
                break;

            case REV32(CIS2):
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

    int32_t SPELRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        OBND.Unload();
        FULL.Unload();
        DESC.Unload();
        MDOB.Unload();
        ETYP.Unload();
        //effects.Unload();

        return 1;
    }

    int32_t SPELRecord::WriteRecord(FileWriter &writer)
    {    
        WRITE(EDID);
        WRITE(OBND);
        WRITE(FULL);
        WRITE(MDOB);
        WRITE(ETYP);
        WRITE(DESC);
        WRITE(SPIT);
        effects.Write(writer);
        return -1;
    }

    bool SPELRecord::operator ==(const SPELRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equalsi(other.FULL) &&
            MDOB == other.MDOB &&
            ETYP == other.ETYP &&
            SPIT == other.SPIT &&
            DESC.equalsi(other.DESC) &&
            effects == other.effects);
    }

    bool SPELRecord::operator !=(const SPELRecord &other) const
    {
        return !(*this == other);
    }

    bool SPELRecord::equals(Record *other)
    {
        return *this == *(SPELRecord *)other;
    }
}