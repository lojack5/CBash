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

	struct WEAPDATA {
		uint32_t value;
		float weight;
		int16_t damage;

		bool operator ==(const WEAPDATA  &other) const {

			return (
				this->value == other.value &&
				this->weight == other.weight &&
				this->damage == other.damage);

		}

		bool operator !=(const WEAPDATA &other) const {
			return !(*this == other);
		}
	};

	struct WEAPDNAM {
		uint32_t animType;
		float speed;
		float reach;
		uint32_t flags;
		float sightFOV;
		uint32_t unk14;
		uint32_t unk18;
		float minRange;
		float maxRange;
		uint32_t unk24;
		uint32_t moreFlags;
		float unk2C;
		float unk30;
		float rumbleLeft;
		float rumbleRight;
		float rumbleDuration;
		uint32_t unk40;
		uint32_t unk44;
		uint32_t unk48;
		uint32_t governingSkill;
		uint32_t unk50;
		uint32_t unk54;
		uint32_t resist;
		uint32_t unk5C;
		float stagger;


		bool operator ==(const WEAPDNAM  &other) const {

			return (
				this->animType == other.animType &&
				this->speed == other.speed &&
				this->reach == other.reach &&
				this->flags == other.flags &&
				this->sightFOV == other.sightFOV &&
				this->unk14 == other.unk14 &&
				this->unk18 == other.unk18 &&
				this->minRange == other.minRange &&
				this->maxRange == other.maxRange &&
				this->unk24 == other.unk24 &&
				this->moreFlags == other.moreFlags &&
				this->unk2C == other.unk2C &&
				this->unk30 == other.unk30 &&
				this->rumbleLeft == other.rumbleLeft &&
				this->rumbleRight == other.rumbleRight &&
				this->rumbleDuration == other.rumbleDuration &&
				this->unk40 == other.unk40 &&
				this->unk44 == other.unk44 &&
				this->unk48 == other.unk48 &&
				this->governingSkill == other.governingSkill &&
				this->unk50 == other.unk50 &&
				this->unk54 == other.unk54 &&
				this->resist == other.resist &&
				this->unk5C == other.unk5C &&
				this->stagger == other.stagger);

		}

		bool operator !=(const WEAPDNAM &other) const {
			return !(*this == other);
		}
	};


	struct WEAPCRDT {
		uint16_t criticalDamage;
		uint16_t unk2;
		float criticalMultiplier;
		uint32_t flags;
		FORMID spellEffect;

		bool operator ==(const WEAPCRDT  &other) const {

			return (
				this->criticalDamage == other.criticalDamage &&
				this->unk2 == other.unk2 &&
				this->criticalMultiplier == other.criticalMultiplier &&
				this->flags == other.flags &&
				this->spellEffect == other.spellEffect);

		}

		bool operator !=(const WEAPCRDT &other) const {
			return !(*this == other);
		}
	};

	class WEAPRecord : public TES5Record // Acoustic Space Record
	{
	public:
		StringRecord EDID; // Editor ID
		VMADRecord VMAD; // VM data
		ReqSubRecord<GENOBND> OBND; // Object Bounds
		LStringRecord FULL; // ambient
		MODEL MODL;
		OptSimpleSubRecord<FORMID> EITM; // Enchantment
		OptSimpleSubRecord<uint16_t, 0> EAMT; // Enchantment Amount
		OptSubRecord<GENDESTRUCT> DEST; // Destruction data
		OptSimpleSubRecord<FORMID> ETYP; // Enchantment
		OptSimpleSubRecord<FORMID> BIDS; // Enchantment
		OptSimpleSubRecord<FORMID> BAMT; // Enchantment
		OptSimpleSubRecord<FORMID> YNAM; // Sound - pick up
		OptSimpleSubRecord<FORMID> ZNAM; // Sound - drop
		OptCounted<OrderedPackedArray<FORMID>, uint32_t, REV32(KSIZ)> KWDA;
		LStringRecord DESC; // Description
		OptSimpleSubRecord<FORMID> INAM;
		OptSimpleSubRecord<FORMID> WNAM;
		OptSimpleSubRecord<FORMID> SNAM;
		OptSimpleSubRecord<FORMID> XNAM;
		OptSimpleSubRecord<FORMID> NAM7;
		OptSimpleSubRecord<FORMID> TNAM;
		OptSimpleSubRecord<FORMID> UNAM;
		OptSimpleSubRecord<FORMID> NAM9;
		OptSimpleSubRecord<FORMID> NAM8;
		OptSubRecord<WEAPDATA> DATA;
		OptSubRecord<WEAPDNAM> DNAM;
		OptSubRecord<WEAPCRDT> CRDT;
		ReqSimpleSubRecord<uint32_t, 0> VNAM;
		OptSimpleSubRecord<FORMID> CNAM;



		WEAPRecord(unsigned char *_recData = NULL);
		WEAPRecord(WEAPRecord *srcRecord);
		~WEAPRecord();

		bool VisitFormIDs(FormIDOp &op);

		uint32_t GetType();
		char * GetStrType();

		int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk = false);
		int32_t Unload();
		int32_t WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

		bool operator ==(const WEAPRecord &other) const;
		bool operator !=(const WEAPRecord &other) const;
		bool equals(Record *other);
	};
}