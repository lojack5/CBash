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
#include "../../ModFile.h"
#include "QUSTRecord.h"
#include <vector>

namespace Sk {


    QUSTRecord::QUSTRecord(unsigned char *_recData) :
        TES5Record(_recData)
    {
        //
    }

    QUSTRecord::QUSTRecord(QUSTRecord *srcRecord) :
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
        VMAD = srcRecord->VMAD;
        FULL = srcRecord->FULL;
        DNAM = srcRecord->DNAM;
        ENAM = srcRecord->ENAM;
        QTGL = srcRecord->QTGL;
        FLTR = srcRecord->FLTR;
        QDCTDA = srcRecord->QDCTDA;
        NEXT = srcRecord->NEXT;
        QECTDA = srcRecord->QECTDA;
        questStages = srcRecord->questStages;
        questObjectives = srcRecord->questObjectives;
        ANAM = srcRecord->ANAM;
        questAliases = srcRecord->questAliases;

        recData = srcRecord->recData;
        if (!srcRecord->IsChanged())
            return;

        return;
    }

    QUSTRecord::~QUSTRecord()
    {
        //
    }

    uint32_t QUSTRecord::GetType()
    {
        return REV32(QUST);
    }

    char * QUSTRecord::GetStrType()
    {
        return "QUST";
    }


    bool QUSTRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;

        for (uint32_t p = 0; p < QTGL.value.size(); p++)
            op.Accept(QTGL.value[p]);

        for (uint32_t p = 0; p < QDCTDA.value.size(); p++)
            QDCTDA.value[p]->VisitFormIDs(op);

        for (uint32_t p = 0; p < QECTDA.value.size(); p++)
            QECTDA.value[p]->VisitFormIDs(op);

        for (uint32_t p = 0; p < questStages.value.size(); p++) {
            for (uint32_t k = 0; k < questStages.value[p]->LOGS.value.size(); k++) {
                if (questStages.value[p]->LOGS.value[k]->NAM0.IsLoaded()) {
                    op.Accept(questStages.value[p]->LOGS.value[k]->NAM0.value);
                }

                for (uint32_t u = 0; u < questStages.value[p]->LOGS.value[k]->CTDA.value.size(); u++) {
                    questStages.value[p]->LOGS.value[k]->CTDA.value[u]->VisitFormIDs(op);
                }
            }
        }

        for (uint32_t p = 0; p < questObjectives.value.size(); p++) {
            for (uint32_t k = 0; k < questObjectives.value[p]->TGTS.value.size(); k++) {
                for (uint32_t u = 0; u < questObjectives.value[p]->TGTS.value[k]->CTDA.value.size(); u++) {
                    questObjectives.value[p]->TGTS.value[k]->CTDA.value[u]->VisitFormIDs(op);
                }
            }
        }

        for (uint32_t p = 0; p < questAliases.value.size(); p++) {
            if (questAliases.value[p]->aliasType != NULL)
                questAliases.value[p]->aliasType->VisitFormIDs(op);

            for (uint32_t k = 0; k < questAliases.value[p]->CTDA.value.size(); k++) {
                questAliases.value[p]->CTDA.value[k]->VisitFormIDs(op);
            }

            for (uint32_t k = 0; k < questAliases.value[p]->KWDA.value.size(); k++) {
                op.Accept(questAliases.value[p]->KWDA.value[k]);
            }

            for (uint32_t k = 0; k < questAliases.value[p]->CNTO.value.size(); k++) {
                op.Accept(questAliases.value[p]->CNTO.value[k].itemID);
            }

            if (questAliases.value[p]->SPOR.IsLoaded()) {
                op.Accept(questAliases.value[p]->SPOR.value);
            }

            if (questAliases.value[p]->OCOR.IsLoaded()) {
                op.Accept(questAliases.value[p]->OCOR.value);
            }

            if (questAliases.value[p]->GWOR.IsLoaded()) {
                op.Accept(questAliases.value[p]->GWOR.value);
            }

            if (questAliases.value[p]->ECOR.IsLoaded()) {
                op.Accept(questAliases.value[p]->ECOR.value);
            }

            if (questAliases.value[p]->ALDN.IsLoaded()) {
                op.Accept(questAliases.value[p]->ALDN.value);
            }

            for (uint32_t k = 0; k < questAliases.value[p]->ALSP.value.size(); k++) {
                op.Accept(questAliases.value[p]->ALSP.value[k]);
            }

            for (uint32_t k = 0; k < questAliases.value[p]->ALFC.value.size(); k++) {
                op.Accept(questAliases.value[p]->ALFC.value[k]);
            }

            for (uint32_t k = 0; k < questAliases.value[p]->ALPC.value.size(); k++) {
                op.Accept(questAliases.value[p]->ALPC.value[k]);
            }

            if (questAliases.value[p]->VTCK.IsLoaded()) {
                op.Accept(questAliases.value[p]->VTCK.value);
            }

        }



        return op.Stop();
    }

    int32_t QUSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        bool isFirst = true;
        bool isQE = false;
        QUSTParseMode mode = QUSTParseMode::QUSTParseNormal;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;

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

            case REV32(VMAD):
                VMAD.Load();
                VMAD.value->Read(buffer, subSize, REV32(QUST), CompressedOnDisk);
                break;

            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;

            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;

            case REV32(QTGL):
                QTGL.Read(buffer, subSize);
                break;

            case REV32(FLTR):
                FLTR.Read(buffer, subSize);
                break;

            case REV32(CTDA): {
                current_condition = new SKCondition();
                switch (mode) {
                case QUSTParseMode::QUSTParseNormal:
                    if (isQE) {
                        QECTDA.value.push_back(current_condition);
                    }
                    else {
                        QDCTDA.value.push_back(current_condition);
                    }
                    break;

                case QUSTParseMode::QUSTParseStages:
                    this->questStages.value.back()->LOGS.value.back()->CTDA.value.push_back(current_condition);
                    break;

                case QUSTParseMode::QUSTParseObjectives:
                    this->questObjectives.value.back()->TGTS.value.back()->CTDA.value.push_back(current_condition);
                    break;

                case QUSTParseMode::QUSTParseAliases:
                    this->questAliases.value.back()->CTDA.value.push_back(current_condition);
                }

                current_condition->CTDA.Read(buffer, subSize);
                break;
            }

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

            case REV32(NEXT):
                NEXT.Read(buffer, subSize, CompressedOnDisk);
                break;

            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;

            case REV32(FNAM): {
                                  switch (mode) {

                                  case QUSTParseMode::QUSTParseObjectives:
                                      this->questObjectives.value.back()->FNAM.Read(buffer, subSize);
                                      break;

                                  case QUSTParseMode::QUSTParseAliases:
                                      this->questAliases.value.back()->FNAM.Read(buffer, subSize);

                                      uint32_t allowedBitmask;
                                      if (this->questAliases.value.back()->isLocation == true) {
                                          allowedBitmask = 0x1030B;
                                      }
                                      else {
                                          allowedBitmask = 0x2FFFF;
                                      }

                                      if ((this->questAliases.value.back()->FNAM.value & (~allowedBitmask)) > 0) {
                                          log_error << "(" << (EDID.IsLoaded() ? EDID.value : "") << ") QUSTRecord::ParseRecords() - FNAM Alias bitmask is wrong ( has unsupported flags ).\n";
                                      }

                                      break;

                                  }
                break;
            }

                //QUSTParseObjectives, parsing objectives.
            case REV32(QOBJ): {
                                  mode = QUSTParseMode::QUSTParseObjectives;
                                  QUSTOBJECTIVE* objective = new QUSTOBJECTIVE();
                                  objective->QOBJ.Read(buffer, subSize);
                                  this->questObjectives.value.push_back(objective);
                                  break;
            }


            case REV32(NNAM): {

                                  if (mode != QUSTParseMode::QUSTParseObjectives) {
                                      throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected NNAM.");
                                  }

                                  this->questObjectives.value.back()->NNAM.Read(buffer, subSize, CompressedOnDisk);
                                  break;
            }

            case REV32(QSTA): {

                                  if (mode != QUSTParseMode::QUSTParseObjectives) {
                                      throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected QSTA.");
                                  }

                                  QUSTCONDITIONALTARGET *newTarget = new QUSTCONDITIONALTARGET();
                                  newTarget->QSTA.Read(buffer, subSize);
                                  this->questObjectives.value.back()->TGTS.value.push_back(newTarget);
                                  break;
            }




                //QUSTParseStages mode, parsing stages.

            case REV32(INDX): {
                                  mode = QUSTParseMode::QUSTParseStages;
                                  QUSTSTAGE* stage = new QUSTSTAGE();
                                  stage->INDX.Read(buffer, subSize);
                                  this->questStages.value.push_back(stage);
                                  break;
            }

            case REV32(CNAM): {

                                  if (mode != QUSTParseMode::QUSTParseStages) {
                                      throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected CNAM.");
                                  }

                                  this->questStages.value.back()->LOGS.value.back()->CNAM.Read(buffer, subSize, CompressedOnDisk);
                                  break;
            }

            case REV32(NAM0): {

                                  if (mode != QUSTParseMode::QUSTParseStages) {
                                      throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected NAM0.");
                                  }

                                  this->questStages.value.back()->LOGS.value.back()->NAM0.Read(buffer, subSize);
                                  break;
            }

            case REV32(QSDT): {

                                  if (mode != QUSTParseMode::QUSTParseStages) {
                                      throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected QSDT.");
                                  }

                                  QUSTLOGENTRY* questLogEntry = new QUSTLOGENTRY();
                                  questLogEntry->QSDT.Read(buffer, subSize);

                                  this->questStages.value.back()->LOGS.value.push_back(questLogEntry);

                                  break;
            }

                //QUSTParseAliases mode.

            case REV32(ALST): {

                                  mode = QUSTParseMode::QUSTParseAliases;
                                  QUSTALIAS *alias = new QUSTALIAS();
                                  alias->aliasID.Read(buffer, subSize);
                                  alias->isLocation = false;
                                  this->questAliases.value.push_back(alias);
                                  break;
            }

            case REV32(ALLS): {
                                  mode = QUSTParseMode::QUSTParseAliases;
                                  QUSTALIAS *alias = new QUSTALIAS();
                                  alias->aliasID.Read(buffer, subSize);
                                  alias->isLocation = true;
                                  this->questAliases.value.push_back(alias);
                                  break;
            }

            case REV32(ALID): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALID.");
                }

                this->questAliases.value.back()->ALID.Read(buffer, subSize, CompressedOnDisk);
                break;
            }

            case REV32(ALFI): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFI.");
                }

                this->questAliases.value.back()->ALFI.Read(buffer, subSize);
                break;
            }

            case REV32(ALCO): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALCO.");
                }

                this->questAliases.value.back()->aliasType = new ALCOAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALEQ): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALEQ.");
                }

                this->questAliases.value.back()->aliasType = new ALEQAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALFA): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFA.");
                }

                if (this->questAliases.value.back()->isLocation == true) {
                    this->questAliases.value.back()->aliasType = new LocALFAAliasFillType();
                }
                else {
                    this->questAliases.value.back()->aliasType = new RefALFAAliasFillType();
                }

                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALFE): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFE.");
                }

                this->questAliases.value.back()->aliasType = new ALFEAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALFL): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFL.");
                }

                this->questAliases.value.back()->aliasType = new ALFLAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALFR): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFR.");
                }

                this->questAliases.value.back()->aliasType = new ALFRAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(ALNA): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALNA.");
                }

                this->questAliases.value.back()->aliasType = new ALNAAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;

            }

            case REV32(ALUA): {
                if (mode != QUSTParseMode::QUSTParseAliases) {
                    throw std::runtime_error("QUSTRecord::ParseRecords() - Unexpected ALFL.");
                }

                this->questAliases.value.back()->aliasType = new ALUAAliasFillType();
                buffer += subSize; // Not implemented, skip sub record
                break;
            }

            case REV32(KWDA): {
                this->questAliases.value.back()->KWDA.Read(buffer, subSize);
                break;
            }

            case REV32(CNTO): {
                this->questAliases.value.back()->CNTO.Read(buffer, subSize);
                break;
            }
            case REV32(SPOR): {
                this->questAliases.value.back()->SPOR.Read(buffer, subSize);
                break;
            }

            case REV32(OCOR): {
                this->questAliases.value.back()->OCOR.Read(buffer, subSize);
                break;
            }

            case REV32(GWOR): {
                this->questAliases.value.back()->GWOR.Read(buffer, subSize);
                break;
            }

            case REV32(ECOR): {
                this->questAliases.value.back()->ECOR.Read(buffer, subSize);
                break;
            }

            case REV32(ALDN): {
                this->questAliases.value.back()->ALDN.Read(buffer, subSize);
                break;
            }

            case REV32(ALSP): {
                this->questAliases.value.back()->ALSP.Read(buffer, subSize);
                break;
            }

            case REV32(ALFC): {
                this->questAliases.value.back()->ALFC.Read(buffer, subSize);
                break;
            }

            case REV32(ALPC): {
                this->questAliases.value.back()->ALPC.Read(buffer, subSize);
                break;
            }

            case REV32(VTCK): {
                this->questAliases.value.back()->VTCK.Read(buffer, subSize);
                break;
            }

            case REV32(ALED):
            case REV32(COCT):
            case REV32(KSIZ): {
                buffer += subSize;
                break; //This is not maintained in memory, just written based on KWDA/CNTO. ALED is just a EOF.
            }

            case REV32(SCHR):
            case REV32(SCTX):
            case REV32(QNAM): {
                buffer += subSize;
                CBASH_SUBTYPE_NOT_IMPLEMENTED
                break;
            }

            default:

                if (mode == QUSTParseMode::QUSTParseAliases) {
                    //Try to proxy the reading to the quest alias type implementation.
                    bool result = this->questAliases.value.back()->aliasType->ParseRecord(buffer, subType, subSize, CompressedOnDisk);

                    if (result == true) {
                        buffer += subSize; // Not implemented, skip sub record
                        break;
                    }
                }

                CBASH_SUBTYPE_UNKNOWN
                CBASH_CHUNK_DEBUG
                buffer = end_buffer;
                break;
            }
        };
        return 0;
    }

    int32_t QUSTRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);

        
        return 1;
    }

    int32_t QUSTRecord::WriteRecord(FileWriter &writer)
    {


        WRITE(EDID); //Editor ID
        VMAD.value->Write(REV32(VMAD), writer); //A bit hacky way to do it.
        WRITE(FULL);
        WRITE(DNAM);
        WRITE(ENAM);
        WRITE(QTGL);
        WRITE(FLTR);
        QDCTDA.Write(writer);
        WRITEEMPTY(NEXT);
        QECTDA.Write(writer);
        questStages.Write(writer);
        questObjectives.Write(writer);
        WRITE(ANAM);
        questAliases.Write(writer);
        return -1;
    }

    bool QUSTRecord::operator ==(const QUSTRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            FULL.equalsi(other.FULL) &&
            DNAM == other.DNAM &&
            ENAM == other.ENAM &&
            QTGL == other.QTGL &&
            FLTR.equalsi(other.FLTR) &&
            QDCTDA == other.QDCTDA &&
            QECTDA == other.QECTDA &&
            ANAM == other.ANAM /* &&
                               TODO, no time for implementing this..
                               questStages == other.questStages &&
                               questObjectives == other.questObjectives &&
                               questAliases == other.questAliases
                               */
                               );
    }

    bool QUSTRecord::operator !=(const QUSTRecord &other) const
    {
        return !(*this == other);
    }

    bool QUSTRecord::equals(Record *other)
    {
        return *this == *(QUSTRecord *)other;
    }

    int32_t  QUSTSTAGE::Write(FileWriter &writer) {
        WRITE(INDX);
        LOGS.Write(writer);
        return -1;
    }

    int32_t  QUSTLOGENTRY::Write(FileWriter &writer) {
        WRITE(QSDT);
        CTDA.Write(writer);
        WRITE(CNAM);
        WRITE(NAM0);
        return -1;
    }

    int32_t  QUSTOBJECTIVE::Write(FileWriter &writer) {
        WRITE(QOBJ);
        WRITE(FNAM);
        WRITE(NNAM);
        TGTS.Write(writer);
        return -1;
    }

    int32_t QUSTCONDITIONALTARGET::Write(FileWriter &writer) {
        WRITE(QSTA);
        CTDA.Write(writer);
        return -1;
    }

    int32_t  QUSTALIAS::Write(FileWriter &writer) {

        if (isLocation == true) {
            writer.record_write_subheader(REV32(ALLS), 4);
        }
        else {
            writer.record_write_subheader(REV32(ALST), 4);
        }

        writer.record_write(&aliasID, 4);

        WRITE(ALID);
        WRITE(FNAM);
        WRITE(ALFI);
        aliasType->WriteRecord(writer);
        CTDA.Write(writer);
        WRITE(KWDA);
        WRITE(CNTO);
        WRITE(SPOR);
        WRITE(OCOR);
        WRITE(GWOR);
        WRITE(ECOR);
        WRITE(ALDN);
        WRITE(ALSP);
        WRITE(ALFC);
        WRITE(ALPC);
        WRITE(VTCK);
        writer.record_write_subheader(REV32(ALED), 0); // alias end

        return -1;
    }

}