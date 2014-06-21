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
#include <vector>

namespace Sk {

	struct INFOPACKDATA {

		uint16_t dialogueTab;
		uint16_t flags;
		float resetTime;
		bool operator ==(const INFOPACKDATA &other) const {
			return (
				this->dialogueTab == other.dialogueTab &&
				this->flags == other.flags &&
				this->resetTime == other.resetTime 
				);
		}

		bool operator !=(const INFOPACKDATA &other) const
		{
			return !(*this == other);
		}

		~INFOPACKDATA() {}

	};

	struct PACKTRDT {
		uint32_t emotionType;
		uint32_t emotionValue;
		uint32_t unk1AlwaysZero;
		uint8_t responseNumber;
		uint8_t junk[3];
		FORMID soundFile;
		uint8_t useEmotionAnimation;
		uint8_t junkTwo[3];

		PACKTRDT() {
			this->emotionType = 0;
			this->emotionValue = 0;
			this->unk1AlwaysZero = 0;
			this->responseNumber = 0;
			for (uint8_t i = 0; i <= 2; ++i) { junk[i] = 0; }
			this->soundFile = 0;
			this->useEmotionAnimation = false;
			for (uint8_t i = 0; i <= 2; ++i) { junkTwo[i] = 0; }
		
		};
		~PACKTRDT() {};

	};

	struct INFORecordResponse {
		ReqSubRecord<PACKTRDT> TRDT;
		StringRecord NAM1;
		StringRecord NAM2;
		StringRecord NAM3;
		OptSimpleSubRecord<FORMID> SNAM;
		OptSimpleSubRecord<FORMID> LNAM;
	};

	class INFORecord : public TES5Record {
	
    public:
        StringRecord EDID; //Editor ID
        //VMAD
		OptSubRecord<INFOPACKDATA> DATA;
		OptSimpleSubRecord<uint32_t> ENAM; //Quest formid
		OptSimpleSubRecord<FORMID> PNAM;
		OptSimpleSubRecord<uint8_t> CNAM;		
		OrderedSparseArray<FORMID> TCLT; //Array of formids to the following topics.
		ReqSimpleSubRecord<FORMID> DNAM; //Dial reference	

		std::vector<INFORecordResponse *> responses; //Array of formids to the following topics.
		OrderedSparseArray<SKCTDA*> CTDA; //Conditions
		
		//SCHR
		
		OptSimpleSubRecord<FORMID> RNAM;
		OptSimpleSubRecord<FORMID> ANAM;
		OptSimpleSubRecord<FORMID> TWAT;
		OptSimpleSubRecord<FORMID> ONAM;
		
		INFORecord(unsigned char *_recData = NULL);
		INFORecord(INFORecord *srcRecord);
		~INFORecord();

		uint32_t  GetType();
		char *  GetStrType();

		bool   VisitFormIDs(FormIDOp &op);

		int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
		int32_t  Unload();
		int32_t  WriteRecord(FileWriter &writer);


        bool operator ==(const INFORecord &other) const;
        bool operator !=(const INFORecord &other) const;
        bool equals(Record *other);

	};


}