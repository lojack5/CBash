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

struct GenXLIG {
	float fov;
	float fade;
	float endDistance;
	float shadowDepth;
	uint32_t unk;
	bool operator ==(const GenXLIG &other) const {
		return (this->fov == other.fov &&
			this->fade == other.fade &&
			this->endDistance == other.endDistance &&
			this->shadowDepth == other.shadowDepth
			);
	}
	bool operator !=(const GenXLIG &other) const {
		return !(*this == other);
	}
};

struct GenXALP {
	uint8_t alphaCutoff;
	uint8_t defaultAlphaCutoff;
	bool operator ==(const GenXALP &other) const {
		return (this->alphaCutoff == other.alphaCutoff &&
			this->defaultAlphaCutoff == other.defaultAlphaCutoff);
	}
	bool operator !=(const GenXALP &other) const {
		return !(*this == other);
	}
};


class REFRRecord : public TES5Record //Texture Set
    {

    public:
        StringRecord EDID; //Editor ID
		OptSubRecord<VMADRecord> VMAD;
		ReqSimpleSubRecord<FORMID> NAME;
		OptSubRecord<GENXMBO> XMBO;
		OptSubRecord<GENXPRM> XPRM; //Primitive
		OptSubRecord<GENXPOD> XPOD; //Portal Data
		OptSubRecord<GENROOM> Room; //Room Data
		OptSimpleSubRecord<FORMID> LNAM; //Light Inherit Flags
		OptSimpleSubRecord<FORMID> INAM; //Light Inherit Flags
		RawRecord XRGD; //Ragdoll Data
		OptSimpleFloatSubRecord<flt_0> XRDS; //Radius
		OptSimpleSubRecord<FORMID, 0> XEMI;
		OptSubRecord<GenXLIG> XLIG;
		OptSubRecord<GENXESP> XESP;
		OptSubRecord<GenXALP> XALP;
		OptSubRecord<GENXNDP> XNDP;
		OptSubRecord<GENXTEL> XTEL;
		OptSimpleFloatSubRecord<flt_0> XSCL;
		SemiOptSimpleSubRecord<uint8_t, 0> XAPD;
		OptSubRecord<GENXAPR> XAPR;
		OptSimpleSubRecord<FORMID, 0> XLIB;
		OptSubRecord<GenXLKR> XLKR;
		OptSubRecord<GenXLOC> XLOC;
		UnorderedSparseArray<FORMID> XLRT;
		OptSimpleSubRecord<FORMID, 0> XOWN;
		OptSimpleSubRecord<int32_t> XRNK;
		OptSimpleSubRecord<uint32_t, 1> XCNT;
		OptSubRecord<COORDINATES> XCVL;
		OptSubRecord<COORDINATES> XCVR;
		OptSimpleSubRecord<FORMID, 0> XCZA;
		OptSimpleSubRecord<FORMID, 0> XCZC;
		OptSimpleSubRecord<FORMID, 0> XEZN;
		OptSimpleFloatSubRecord<flt_0> XFVC;
		SemiOptSimpleSubRecord<uint8_t, 0> FNAM;
		NonNullStringRecord FULL;
		OptSimpleSubRecord<uint16_t, 0> TNAM;
		OptSimpleFloatSubRecord<flt_0> XHTW;
		//XIS2
		SemiOptSimpleSubRecord<uint32_t, 0> XLCM;
		OptSimpleSubRecord<FORMID, 0> XMBR;
		RawRecord XMRK;
		//XOCP
		UnorderedSparseArray<FORMID> XPWR;
		SemiOptSimpleSubRecord<uint32_t, 0> XTRI;
		//ONAM
		OptSimpleSubRecord<uint32_t, 0> XACT;
		OptSimpleSubRecord<FORMID> XTNM;
		RawRecord XIS2;
		SemiOptSimpleSubRecord<uint32_t, 0> XWCN;

		OptSimpleFloatSubRecord<flt_0> XPRD;

		bool openByDefault = false; //ONAM set

		OptSimpleSubRecord<FORMID, 0> XATR;

		OptCounted<UnorderedPackedArray<struct XWCU>, uint32_t, REV32(XWCN)> XWCU; // Keywords

		OptSubRecord<GENPOSDATA> DATA; //Position/Rotation

		REFRRecord(unsigned char *_recData = NULL);
		REFRRecord(REFRRecord *srcRecord);
		~REFRRecord();

		uint32_t  GetType();
		char *  GetStrType();

		bool   VisitFormIDs(FormIDOp &op);

		int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
		int32_t  Unload();
		int32_t  WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }


        bool operator ==(const REFRRecord &other) const;
        bool operator !=(const REFRRecord &other) const;
        bool equals(Record *other);
    };
}