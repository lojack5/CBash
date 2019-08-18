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
#include "../../Common.h"
#include "../../GenericRecord.h"
#include "../VMAD/VMAD.h"
#include "../SkyrimChunks.h"

namespace Sk
{

	struct GenPDTO {

		uint32_t type;
		union {
			FORMID subtype;
			char str[4];
		} sub;
		
		bool operator ==(const GenPDTO &other) const {
			
			if (this->type != other.type) {
				return false;
			}

			switch (this->type) {
				case 1: {
					return this->sub.subtype == other.sub.subtype;
				}

				case 2:
				default: {
					return this->sub.str == other.sub.str;
				}

			}

		}

		bool operator !=(const GenPDTO &other) const {
			return !(*this == other);
		}
	};

	class ACHRRecord : public TES5Record //Texture Set
	{

	public:
		StringRecord EDID; //Editor ID
		OptSubRecord<VMADRecord> VMAD;
		ReqSimpleSubRecord<FORMID> NAME;
		OptSimpleSubRecord<FORMID> XEZN;
		OptSimpleFloatSubRecord<flt_0> XPRD; //Radius
		RawRecord XPPA;
		OptSimpleSubRecord<FORMID> INAM; //Light Inherit Flags
		OptSubRecord<GenPDTO> PDTO;
		RawRecord XRGD;
		RawRecord XRGB;
		SemiOptSimpleSubRecord<uint32_t, 0> XLCM; //Light Inherit Flags
		SemiOptSimpleSubRecord<uint8_t, 0> XAPD; //Light Inherit Flags
		OptSubRecord<GENXAPR> XAPR;
		UnorderedSparseArray<FORMID> XLRT;
		OptSimpleSubRecord<FORMID, 0> XHOR;
		OptSubRecord<GENXESP> XESP;
		OptSimpleSubRecord<FORMID, 0> XOWN;
		OptSimpleSubRecord<FORMID, 0> XLCN;
		OptSubRecord<GenXLKR> XLKR;
		RawRecord XIS2;
		OptSimpleSubRecord<FORMID, 0> XLRL;
		SemiOptSimpleFloatSubRecord<flt_0> XSCL; //Hair length
		OptSubRecord<GENPOSDATA> DATA; //Position/Rotation

		ACHRRecord(unsigned char *_recData = NULL);
		ACHRRecord(ACHRRecord *srcRecord);
		~ACHRRecord();

		uint32_t  GetType();
		char *  GetStrType();

		bool   VisitFormIDs(FormIDOp &op);

		int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
		int32_t  Unload();
		int32_t  WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }


		bool operator ==(const ACHRRecord &other) const;
		bool operator !=(const ACHRRecord &other) const;
		bool equals(Record *other);
	};
}