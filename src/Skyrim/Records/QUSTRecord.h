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
#include "../../GenericRecord.h"
#include "../SkyrimChunks.h"
#include "../SkyrimCommon.h"
#include "../VMAD/VMAD.h"
#include <vector>

namespace Sk {

	enum QUSTParseMode {
		QUSTParseNormal = 0,
		QUSTParseStages = 1,
		QUSTParseObjectives = 2,
		QUSTParseAliases = 3
	};

    class IAliasFillType {

    public:
        virtual void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) = 0;
        virtual bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) = 0;
        virtual void VisitFormIDs(FormIDOp& op) = 0;
        virtual void WriteRecord(FileWriter &writer) = 0;
    };

    class ALCOAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<FORMID> ALCO;
        OptSimpleSubRecord<uint32_t> ALCA;
        OptSimpleSubRecord<uint32_t> ALCL;

        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALCO.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(ALCA):
                this->ALCA.Read(buffer, subSize);
                break;

            case REV32(ALCL):
                this->ALCL.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALCO.value);

        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALCO);
            WRITE(ALCA);
            WRITE(ALCL);
        }
    };

    class ALEQAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<FORMID> ALEQ;
        OptSimpleSubRecord<uint32_t> ALEA;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALEQ.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(ALEA):
                this->ALEA.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALEQ.value);

        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALEQ);
            WRITE(ALEA);
        }
    };
    class LocALFAAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<uint32_t> ALFA;
        OptSimpleSubRecord<uint32_t> KNAM;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALFA.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(KNAM):
                this->KNAM.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->KNAM.value);

        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALFA);
            WRITE(KNAM);
        }
    };
    class RefALFAAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<uint32_t> ALFA;
        OptSimpleSubRecord<uint32_t> ALRT;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALFA.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(ALRT):
                this->ALRT.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALRT.value);

        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALFA);
            WRITE(ALRT);
        }
    };
    class ALFEAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<uint32_t> ALFE;
        OptSimpleSubRecord<uint32_t> ALFD;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALFE.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(ALFD):
                this->ALFD.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            //Empty.
        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALFE);
            WRITE(ALFD);
        }
    };
    class ALFLAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<FORMID> ALFL;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALFL.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            return false;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALFL.value);
            //Empty.
        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALFL);
        }
    };
    class ALFRAliasFillType : public IAliasFillType {
    public:
        ReqSimpleSubRecord<FORMID> ALFR;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALFR.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            return false;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALFR.value);
            //Empty.
        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALFR);
        }
    };
    class ALNAAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<uint32_t> ALNA;
        OptSimpleSubRecord<uint32_t> ALNT;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALNA.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            switch (subType) {

            case REV32(ALNT):
                this->ALNT.Read(buffer, subSize);
                break;

            default:
                return false;

            }

            return true;

        }
        void VisitFormIDs(FormIDOp& op) {
            //Empty
        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALNA);
            WRITE(ALNT);
        }
    };
    class ALUAAliasFillType : public IAliasFillType {

        ReqSimpleSubRecord<FORMID> ALUA;
        void ParseHead(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            this->ALUA.Read(buffer, subSize);

        }

        bool ParseRecord(unsigned char *buffer, uint32_t subType, uint32_t subSize, bool CompressedOnDisk = false) {

            return false;

        }
        void VisitFormIDs(FormIDOp& op) {
            op.Accept(this->ALUA.value);
            //Empty.
        }
        void WriteRecord(FileWriter &writer) {
            WRITE(ALUA);
        }
    };

	struct QUSTDATA {
		uint8_t encounterFlags;
		uint8_t generalFlags;
		uint8_t priority;
		uint8_t unknownUsuallyZero;
		int32_t unknownAlwaysZero;
		uint32_t questType;

        bool operator ==(const QUSTDATA &other) const {

            return (this->encounterFlags == other.encounterFlags &&
                    this->generalFlags == other.generalFlags &&
                    this->priority == other.priority &&
                    this->unknownAlwaysZero == other.unknownAlwaysZero &&
                    this->unknownUsuallyZero == other.unknownUsuallyZero &&
                    this->questType == other.questType                
                );

        }
        bool operator !=(const QUSTDATA &other) const {
            return !(*this == other);
        }

	};

	struct QUSTTARGET {
		int32_t targetAlias;
		int32_t flags;
	};

	struct QUSTCONDITIONALTARGET {

		ReqSubRecord<QUSTTARGET> QSTA;
		OrderedSparseArray<SKCondition*> CTDA;

		int32_t  Write(FileWriter &writer);
	};

	struct QUSTOBJECTIVE {
		ReqSimpleSubRecord<int16_t> QOBJ;
		ReqSimpleSubRecord<int32_t> FNAM;
        StringRecord NNAM;
		UnorderedSparseArray<QUSTCONDITIONALTARGET*> TGTS;

        int32_t  Write(FileWriter &writer);
	};

	struct QUSTINDEX {

		int16_t journalIndex;
		int8_t flags;
		int8_t unknown;

	};

	struct QUSTLOGENTRY {
		ReqSimpleSubRecord<uint8_t> QSDT;
		OrderedSparseArray<SKCondition*> CTDA;
        StringRecord CNAM;
		OptSimpleSubRecord<FORMID> NAM0;
		int32_t  Write(FileWriter &writer);
	};

	struct QUSTSTAGE {

		ReqSubRecord<QUSTINDEX> INDX;
		UnorderedSparseArray<QUSTLOGENTRY*> LOGS;
        int32_t  Write(FileWriter &writer);
	};

	struct QUSTALIAS {

		ReqSimpleSubRecord<uint32_t> aliasID;
		
		bool isLocation;
		StringRecord ALID;

		ReqSimpleSubRecord<uint32_t> FNAM;
		OptSimpleSubRecord<uint32_t> ALFI;
		IAliasFillType* aliasType;

		UnorderedSparseArray<SKCondition*> CTDA;

		OptCounted<OrderedPackedArray<FORMID>, uint32_t, REV32(KSIZ)> KWDA;

		OptCounted<UnorderedSparseArray<ContainerItems>, uint32_t, REV32(COCT)> CNTO;

		OptSimpleSubRecord<FORMID> SPOR;
		OptSimpleSubRecord<FORMID> OCOR;
		OptSimpleSubRecord<FORMID> GWOR;
		OptSimpleSubRecord<FORMID> ECOR;
		OptSimpleSubRecord<FORMID> ALDN;

		UnorderedSparseArray<FORMID> ALSP;
		UnorderedSparseArray<FORMID> ALFC;
		UnorderedSparseArray<FORMID> ALPC;
		OptSimpleSubRecord<FORMID> VTCK;
		RawRecord ALED;

		int32_t  Write(FileWriter &writer);
		
	};

	class QUSTRecord : public TES5Record {
	
    public:
        StringRecord EDID; //Editor ID
        //VMAD
		OptSubRecord<VMADRecord> VMAD;
        StringRecord FULL;
		ReqSubRecord<QUSTDATA> DNAM;
		OptSubRecord<char*> ENAM;
		UnorderedSparseArray<FORMID> QTGL;
		UnorderedPackedStrings FLTR;
		UnorderedSparseArray<SKCondition*> QDCTDA;
		RawRecord NEXT;
		UnorderedSparseArray<SKCondition*> QECTDA;

		UnorderedSparseArray<QUSTSTAGE*> questStages;
		UnorderedSparseArray<QUSTOBJECTIVE*> questObjectives;

		ReqSimpleSubRecord<int32_t> ANAM;

		UnorderedSparseArray<QUSTALIAS*> questAliases;
		
		//SCHR
		
		QUSTRecord(unsigned char *_recData = NULL);
		QUSTRecord(QUSTRecord *srcRecord);
		~QUSTRecord();

		uint32_t  GetType();
		char *  GetStrType();

		bool   VisitFormIDs(FormIDOp &op);

		int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
		int32_t  Unload();
		int32_t  WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }


		bool operator ==(const QUSTRecord &other) const;
		bool operator !=(const QUSTRecord &other) const;
        bool equals(Record *other);

	};


}