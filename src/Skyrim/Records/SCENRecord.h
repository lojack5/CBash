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
*  Jacob "Lojack" Lojewski
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
#include "../../GenericRecord.h"
#include "../SkyrimChunks.h"
#include "../SkyrimCommon.h"

namespace Sk {

	class SCENRecord : public TES5Record // Acoustic Space Record
	{
	public:

		struct SCENPhase {
			RawRecord SHNAM;
			StringRecord NAM0;
			OrderedSparseArray<SKCondition*> SCTDA;
			OrderedSparseArray<SKCondition*> CCTDA;
			ReqSimpleSubRecord<uint32_t> WNAM;
			RawRecord EHNAM;
			//Conditions
		};

		struct SCENActor {
			ReqSimpleSubRecord<uint32_t> ALID;
			OptSimpleSubRecord<uint32_t> LNAM;
			OptSimpleSubRecord<uint32_t> DNAM;

		};

		struct SCENActionData {
			virtual bool Read(uint32_t type, unsigned char *&buffer, const uint32_t &subSize) = 0;
		};

		struct DialogueSCENActionData : SCENActionData {
			ReqSimpleSubRecord<FORMID> DATA;
			OptSimpleSubRecord<int32_t> HTID;
			OptSimpleFloatSubRecord<flt_0> DMAX;
			OptSimpleFloatSubRecord<flt_0> DMIN;
			OptSimpleSubRecord<uint32_t> DEMO;
			OptSimpleSubRecord<uint32_t> DEVA;

			bool Read(uint32_t type, unsigned char *&buffer, const uint32_t &subSize) {
				switch (type)
				{
					case REV32(DATA): {
						DATA.Read(buffer, subSize);
						break;
					}
					case REV32(HTID): {
						HTID.Read(buffer, subSize);
						break;
					}
					case REV32(DMAX): {
						DMAX.Read(buffer, subSize);
						break;
					}
					case REV32(DMIN): {
						DMIN.Read(buffer, subSize);
						break;
					}
					case REV32(DEMO): {
						DEMO.Read(buffer, subSize);
						break;
					}
					case REV32(DEVA): {
						DEVA.Read(buffer, subSize);
						break;
					}
				}

				return true;
			}
		};

		struct PackageSCENActionData : SCENActionData {
			UnorderedSparseArray<FORMID> PNAM; //Might be packed
			bool Read(uint32_t type, unsigned char *&buffer, const uint32_t &subSize) {
				switch (type) {
					case REV32(PNAM): {
						PNAM.Read(buffer, subSize);
						break;
					}
				}
				return true;

			}
		};

		struct TimerSCENActionData : SCENActionData {

			ReqSimpleFloatSubRecord<flt_0> SNAM;
			bool Read(uint32_t type, unsigned char *&buffer, const uint32_t &subSize) {
				switch (type) {
					case REV32(SNAM): {
						SNAM.Read(buffer, subSize);
						break;
					}
				}

				return true;

			}
		};

		struct SCENAction {
			ReqSimpleSubRecord<uint16_t> ANAM;
			StringRecord NAM0;
			ReqSimpleSubRecord<uint32_t> ALID;
			ReqSimpleSubRecord<uint32_t> INAM;
			OptSimpleSubRecord<uint32_t> FNAM;
			ReqSimpleSubRecord<uint32_t> SNAM;
			ReqSimpleSubRecord<uint32_t> ENAM;
			SCENActionData *actionData;
		};

		struct SCENBehaviorSettings {
			uint32_t setAllNormal;
			uint32_t setAllPause;
			uint32_t setAllEnd;
			uint32_t dontSetAll;

			bool operator ==(const SCENBehaviorSettings &other) const
			{
				return (setAllNormal == other.setAllNormal &&
						setAllPause == other.setAllPause &&
						setAllEnd == other.setAllEnd &&
						dontSetAll == other.dontSetAll
					);
			}
		};


		StringRecord EDID; // Editor ID
		OptSubRecord<VMADRecord> VMAD;
		ReqSimpleSubRecord<uint32_t> FNAM;
		std::vector<SCENPhase*> phases;
		std::vector<SCENActor*> actors;
		std::vector<SCENAction*> actions;
		ReqSimpleSubRecord<FORMID> PNAM; //Parent quest
		ReqSimpleSubRecord<uint32_t> INAM;
		ReqSubRecord<struct SCENBehaviorSettings> VNAM;
		OrderedSparseArray<SKCondition*> CTDA; //Conditions


		ReqSimpleFloatSubRecord<flt_0> FLTV;

		SCENRecord(unsigned char *_recData = NULL);
		SCENRecord(SCENRecord *srcRecord);
		~SCENRecord();

		bool VisitFormIDs(FormIDOp &op);

		uint32_t GetType();
		char * GetStrType();

		int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk = false);
		int32_t Unload();
		int32_t WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

		bool operator ==(const SCENRecord &other) const;
		bool operator !=(const SCENRecord &other) const;
		bool equals(Record *other);
	};
}