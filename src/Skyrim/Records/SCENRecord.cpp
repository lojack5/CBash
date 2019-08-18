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
#include "SCENRecord.h"

namespace Sk
{
    SCENRecord::SCENRecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    SCENRecord::SCENRecord(SCENRecord *srcRecord) :
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
        FNAM = srcRecord->FNAM;
        PNAM = srcRecord->PNAM;
        INAM = srcRecord->INAM;
        VNAM = srcRecord->VNAM;
        CTDA = srcRecord->CTDA;


        return;
    }

    SCENRecord::~SCENRecord()
    {
        //
    }

    uint32_t SCENRecord::GetType()
    {
        return REV32(SCEN);
    }

    char * SCENRecord::GetStrType()
    {
        return "SCEN";
    }


    bool SCENRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;
        if (VMAD.IsLoaded()) {
            //TODO - implement VisitFormIDs for struct VMADRecord
        }
        op.Accept(PNAM.value);
        //TODO - implement VisitFormIDs for struct struct SCENBehaviorSettings

        if (CTDA.IsLoaded()) {
            //TODO - implement VisitFormIDs for struct SKCondition*
        }

        return op.Stop();
    }


    int32_t SCENRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;

        struct SCENPhase  *current_phase = NULL;
        struct SCENActor  *current_actor = NULL;
        struct SCENAction *current_action = NULL;

        bool hasReadStartPhase = false;

        uint32_t parsingPhase = 0; //0 = before phases, 1 = phases, 2 = actors, 3 = actions, 4 = after actions
        uint32_t phasePhase = 0; //0 = phase start, 1 = first NEXT, 2 = second next

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
                VMAD.Load();
                VMAD.value->Read(buffer, subSize, REV32(SCEN), CompressedOnDisk);
                break;
            case REV32(FNAM):
                if (parsingPhase == 0) {
                    FNAM.Read(buffer, subSize);
                }
                else if (parsingPhase == 3) {
                    current_action->FNAM.Read(buffer, subSize);
                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                break;
            case REV32(PNAM):
                if (parsingPhase == 0) {
                    PNAM.Read(buffer, subSize);
                }
                else if (parsingPhase == 3) {
                    //PNAM for the action data
                    current_action->actionData->Read(REV32(PNAM), buffer, subSize);
                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                break;
            case REV32(INAM):
                if (parsingPhase == 3) {
                    current_action->INAM.Read(buffer, subSize);
                }
                else if (parsingPhase == 4) {
                    INAM.Read(buffer, subSize);
                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                break;
            case REV32(HNAM):
            {
                if (parsingPhase < 1) {
                    parsingPhase = 1;
                }

                current_phase = new SCENPhase();
                phasePhase = 0;
                phases.push_back(current_phase);

            }
            case REV32(NAM0): {

                if (parsingPhase == 1) {
                    current_phase->NAM0.Read(buffer, subSize, CompressedOnDisk);
                }
                else if(parsingPhase == 3) {
                    current_action->NAM0.Read(buffer, subSize, CompressedOnDisk);
                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }

                break;
            }
            case REV32(CTDA): {
                if (parsingPhase == 0) {
                    CTDA.Read(buffer, subSize);
                }
                else if (parsingPhase == 1) {
                    if (phasePhase == 0) {
                        current_phase->SCTDA.Read(buffer, subSize);
                    }
                    else if (phasePhase == 1) {
                        current_phase->CCTDA.Read(buffer, subSize);
                    }
                    else {
                        printer("SCEN: %08X - Unknown phasePhase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %08x\n\n", buffer - 6);
                        buffer = end_buffer;
                    }

                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                break;
            }
            case REV32(WNAM): {
                current_phase->WNAM.Read(buffer, subSize);
                break;
            }
            case REV32(ALID): {
                if (parsingPhase < 2) {
                    parsingPhase = 2;
                }

                if (parsingPhase == 2) {
                    current_actor = new SCENActor();
                    actors.push_back(current_actor);
                }
                else if (parsingPhase == 3) {
                    current_action->ALID.Read(buffer, subSize);
                }
                else {
                    printer("SCEN: %08X - Unknown parsing_phase for subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %08x\n\n", buffer - 6);
                    buffer = end_buffer;
                }
                break;
            }
            case REV32(LNAM): {
                current_actor->LNAM.Read(buffer, subSize);
                break;
            }
            case REV32(DNAM): {
                current_actor->DNAM.Read(buffer, subSize);
                break;
            }
            case REV32(ANAM): {
                if (parsingPhase < 3) {
                    parsingPhase = 3;
                }

                hasReadStartPhase = false;
                current_action = new SCENAction();
                current_action->ANAM.Read(buffer, subSize);

                switch (current_action->ANAM.value) {
                    case 0: {
                        current_action->actionData = new DialogueSCENActionData();
                        break;
                    }
                    case 1: {
                        current_action->actionData = new PackageSCENActionData();
                        break;
                    }
                    case 2: {
                        current_action->actionData = new TimerSCENActionData();
                        break;
                    }
                }

                break;
            }
            case REV32(NEXT): {
                phasePhase++;
                break;
            }
            case REV32(SNAM):
                if (!hasReadStartPhase) {
                    current_action->SNAM.Read(buffer, subSize);
                    hasReadStartPhase = true;
                }
                else {
                    current_action->actionData->Read(REV32(SNAM), buffer, subSize);
                }
                break;
            case REV32(ENAM):
                current_action->ENAM.Read(buffer, subSize);
                break;
            case REV32(VNAM):
                VNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
            case REV32(HTID):
            case REV32(DMAX):
            case REV32(DMIN):
            case REV32(DEMO):
            case REV32(DEVA): {
                current_action->actionData->Read(subType, buffer, subSize);
            }

            default:
                CBASH_SUBTYPE_UNKNOWN
                CBASH_CHUNK_DEBUG
                buffer = end_buffer;
                break;
            }
        };
        return 0;
    }

    int32_t SCENRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        VMAD.Unload();
        FNAM.Unload();
        PNAM.Unload();
        INAM.Unload();
        VNAM.Unload();
        CTDA.Unload();

        return 1;
    }

    int32_t SCENRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(FNAM);
        WRITE(PNAM);
        WRITE(INAM);
        WRITE(VNAM);
        WRITE(CTDA);
        return -1;
    }

    bool SCENRecord::operator ==(const SCENRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            FNAM == other.FNAM &&
            PNAM == other.PNAM &&
            INAM == other.INAM &&
            VNAM == other.VNAM &&
            CTDA == other.CTDA);
    }

    bool SCENRecord::operator !=(const SCENRecord &other) const
    {
        return !(*this == other);
    }

    bool SCENRecord::equals(Record *other)
    {
        return *this == *(SCENRecord *)other;
    }
}