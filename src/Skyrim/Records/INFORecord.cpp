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
#pragma once
// BaseRecord.h
#include "../../Common.h"
#include "../../GenericChunks.h"
#include "INFORecord.h"
#include <vector>

namespace Sk {


    INFORecord::INFORecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    INFORecord::INFORecord(INFORecord *srcRecord) :
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
        
        EDID = srcRecord->EDID;
        DATA = srcRecord->DATA;
        ENAM = srcRecord->ENAM;
        PNAM = srcRecord->PNAM;
        CNAM = srcRecord->CNAM;
        TCLT = srcRecord->TCLT;
        DNAM = srcRecord->DNAM;
        responses = srcRecord->responses;
        CTDA = srcRecord->CTDA;
        RNAM = srcRecord->RNAM;
        ANAM = srcRecord->ANAM;
        TWAT = srcRecord->TWAT;
        ONAM = srcRecord->ONAM;
        VMAD = srcRecord->VMAD;

        recData = srcRecord->recData;
        if (!srcRecord->IsChanged())
            return;

        return;
    }

    INFORecord::~INFORecord()
    {
        //
    }

    uint32_t INFORecord::GetType()
    {
        return REV32(INFO);
    }

    char * INFORecord::GetStrType()
    {
        return "INFO";
    }


    bool INFORecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;

        if (PNAM.IsLoaded()) {
            op.Accept(PNAM.value);
        }

        for (uint32_t ListIndex = 0; ListIndex < TCLT.value.size(); ListIndex++)
            op.Accept(TCLT.value[ListIndex]);

        op.Accept(DNAM.value);

        if (RNAM.IsLoaded()) {
            op.Accept(RNAM.value);
        }

        //REVERT ASAP!
        if (ANAM.IsLoaded()) {
            op.Accept(ANAM.value);
        }

        if (TWAT.IsLoaded()) {
            op.Accept(TWAT.value);
        }

        if (ONAM.IsLoaded()) {
            op.Accept(ONAM.value);
        }

        return op.Stop();
    }

    int32_t INFORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        INFORecordResponse* response = new INFORecordResponse();
        bool isFirst = true;
        SKCondition *current_condition = NULL;

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

            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;

            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;

            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;

            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;

            case REV32(TCLT):
                TCLT.Read(buffer, subSize);
                break;

            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;

            case REV32(VMAD):
                VMAD.Load();
                VMAD.value->Read(buffer, subSize, REV32(INFO), CompressedOnDisk);
                break;

            case REV32(TRDT):
                if (!isFirst) {
                    this->responses.push_back(response);
                    INFORecordResponse* response = new INFORecordResponse();
                }
                else {
                    isFirst = false;
                }
                response->TRDT.Read(buffer, subSize);
                break;

            case REV32(NAM1):
                if (response == NULL) {
                    throw std::runtime_error("Wrong responses format in INFO");
                }
                response->NAM1.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(NAM2):
                if (response == NULL) {
                    throw std::runtime_error("Wrong responses format in INFO");
                }
                response->NAM2.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(NAM3):
                if (response == NULL) {
                    throw std::runtime_error("Wrong responses format in INFO");
                }
                response->NAM3.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(SNAM):
                if (response == NULL) {
                    throw std::runtime_error("Wrong responses format in INFO");
                }
                response->SNAM.Read(buffer, subSize);
                break;

            case REV32(LNAM):
                if (response == NULL) {
                    throw std::runtime_error("Wrong responses format in INFO");
                }
                response->LNAM.Read(buffer, subSize);
                break;

            case REV32(CTDA):
                current_condition = new SKCondition();
                CTDA.value.push_back(current_condition);
                current_condition->CTDA.Read(buffer, subSize);
                break;


            case REV32(CIS1):
                if (current_condition == NULL) {
                    printer("  INFO: %08X - Reading CIS1 without current_condition set\n", formID);
                    CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                else {
                    current_condition->CIS1.Read(buffer, subSize, CompressedOnDisk);
                }

                break;

            case REV32(CIS2):
                if (current_condition == NULL) {
                    printer("  INFO: %08X - Reading CIS2 without current_condition set\n", formID);
                    CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                else {
                    current_condition->CIS2.Read(buffer, subSize, CompressedOnDisk);
                }

                break;

            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;

            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;

            case REV32(TWAT):
                TWAT.Read(buffer, subSize);
                break;

            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;

			case REV32(SCHR):
				// not implemented yet
				buffer = end_buffer;
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

    int32_t INFORecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);


        EDID.Unload();
        DATA.Unload();
        ENAM.Unload();
        PNAM.Unload();
        CNAM.Unload();
        TCLT.Unload();
        DNAM.Unload();
        VMAD.Unload();
        
        for (uint32_t i = 0; i < responses.size(); ++i) {
            
            /*
            responses[i]->TRDT.Unload();
            */
            responses[i]->NAM1.Unload();
            responses[i]->NAM2.Unload();
            responses[i]->NAM3.Unload();
            responses[i]->SNAM.Unload();
            responses[i]->LNAM.Unload();
            delete responses[i];
        }


        CTDA.Unload();
        RNAM.Unload();
        ANAM.Unload();
        TWAT.Unload();
        ONAM.Unload();
        return 1;
    }

    int32_t INFORecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);

        if (VMAD.IsLoaded()) {
            VMAD.value->Write(REV32(VMAD), writer); //A bit hacky way to do it.
        }
        WRITE(DATA);
        WRITE(ENAM);
        WRITE(PNAM);
        WRITE(CNAM);
        WRITE(TCLT);
        WRITE(DNAM);

        for (uint32_t i = 0; i < responses.size(); ++i) {
            
            responses[i]->TRDT.Write(REV32(TRDT),writer);
            responses[i]->NAM1.Write(REV32(NAM1), writer);
            responses[i]->NAM2.Write(REV32(NAM2), writer);
            responses[i]->NAM3.Write(REV32(NAM3), writer);
            responses[i]->SNAM.Write(REV32(SNAM), writer);
            responses[i]->LNAM.Write(REV32(LNAM), writer);
        }

        CTDA.Write(writer);
        WRITE(RNAM);
        WRITE(ANAM);
        WRITE(TWAT);
        WRITE(ONAM);
        return -1;
    }

    bool INFORecord::operator ==(const INFORecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA &&
            ENAM == other.ENAM &&
            PNAM == other.PNAM &&
            CNAM == other.CNAM &&
            TCLT == other.TCLT &&
            DNAM == other.DNAM &&
            responses == other.responses &&
            CTDA == other.CTDA &&
            RNAM == other.RNAM &&
            ANAM == other.ANAM &&
            TWAT == other.TWAT &&
            ONAM == other.ONAM
            );
    }

    bool INFORecord::operator !=(const INFORecord &other) const
    {
        return !(*this == other);
    }

    bool INFORecord::equals(Record *other)
    {
        return *this == *(INFORecord *)other;
    }

}