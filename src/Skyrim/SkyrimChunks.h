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

#include "../GenericChunks.h"

namespace Sk {

// LVLO subrecord for leveled lists.  Different than previous games
// in that 'level' is a uint16_t now instead of a int16_t
struct SKLVLO
    {
        uint16_t  level;
        uint8_t   unused1[2];
        FORMID  listId;
        int16_t  count;
        uint8_t   unused2[2];

        SKLVLO();
        ~SKLVLO();

        void Write(FileWriter &writer);

        bool operator ==(const SKLVLO &other) const;
        bool operator !=(const SKLVLO &other) const;
    };
SIZE_CHECK(SKLVLO, 12);

// LVLO/COED pair for LVLI records
struct SKLVLOCOED
    {
        ReqSubRecord<SKLVLO> LVLO;
        OptSubRecord<GENCOED> COED;

        bool IsGlobal() const;
        bool IsRank() const;

        void Write(FileWriter &writer);

        bool operator ==(const SKLVLOCOED &other) const;
        bool operator !=(const SKLVLOCOED &other) const;
    };

// CNTO/COED pair for NPC_ records
struct SKCNTOCOED
    {
        ReqSubRecord<GENCNTO> CNTO;
        OptSubRecord<GENCOED> COED;

        bool IsGlobal() const;
        bool IsRank() const;

        void Write(FileWriter &writer);

        bool operator ==(const SKCNTOCOED &other) const;
        bool operator !=(const SKCNTOCOED &other) const;
    };

struct MODEL
    {
        StringRecord MODL;  // Model Filename
        RawRecord MODT;     // Texture Files Hashes

        MODEL();
        ~MODEL();

        void Write(FileWriter &write);

        bool operator ==(const MODEL &other) const;
        bool operator !=(const MODEL &other) const;
    };

struct GENCNAM  // Color
    {
        uint8_t red, green, blue, unk1; // unk in xEdit, unused on UESPWiki

        GENCNAM();
        ~GENCNAM();

        bool operator == (const GENCNAM &other) const;
        bool operator != (const GENCNAM &other) const;
    };
SIZE_CHECK(GENCNAM, 4);

struct SKDESTSTAGE
{
    ReqSubRecord<DESTDSTD> DSTD;
    StringRecord DMDL;
    RawRecord DMDT;
    FNVAlternateTextures DMDS;

    void Write(FileWriter &writer);
    void VisitFormIDs(FormIDOp &op);

    bool operator == (const SKDESTSTAGE &other) const;
    bool operator != (const SKDESTSTAGE &other) const;
};
struct sortSKDESTStages
{
    bool operator()(const SKDESTSTAGE *lhs, const SKDESTSTAGE *rhs) const;
};

struct SKDESTRUCT //Destructable
{
    ReqSubRecord<GENDEST> DEST; //Destructable Header
    OrderedSparseArray<SKDESTSTAGE *, sortSKDESTStages> Stages; //Destructable Stages

    enum flagsFlags
    {
        fIsVATSTargetable = 0x01
    };

    void Write(FileWriter &writer);
    void VisitFormIDs(FormIDOp &op);

    bool operator == (const SKDESTRUCT &other) const;
    bool operator != (const SKDESTRUCT &other) const;
};

struct SKCTDA //Condition
{
    uint8_t   operType, unused1[3]; //Type, Unused
    FORMID_OR_FLOAT32 compValue; //Float or Global (if fIsUseGlobal is true)
    uint16_t  ifunc; // function index
    uint8_t   unused2[2]; // padding
    FORMID_OR_UINT32 param1, param2;
    //Below are not always present on chunk...
    uint32_t  runOnType; //Run On
    FORMID_OR_UINT32 reference; //Reference (if runOn == 2) or Unused
    int32_t  param3;

    enum operTypeType
    {
        eEqual = 0<<5,
        eNotEqual = 1<<5,
        eGreater = 2<<5,
        eGreaterOrEqual = 3<<5,
        eLess = 4<<5,
        eLessOrEqual = 5<<5,
        eOperTypeMask = 0xE0 // First 3 bits
    };

    enum operTypeFlag
    {
        fIsNone = 0x00,
        fIsOr = 0x01,
        fIsUseAliases = 0x02,
        fIsUseGlobal = 0x04,
        fIsUsePackData = 0x08,
        fIsSwapSubject = 0x10,
        fOperFlagMask = 0x1F // Last 5 bits
    };

    enum operRunOnType
    {
        eSubject = 0,
        eTarget,
        eReference,
        eCombatTarget,
        eLinkedReference,
        eQuestAlias,
        ePackageData,
        eEventData
    };

    SKCTDA();
    ~SKCTDA();

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const SKCTDA &other) const;
    bool operator !=(const SKCTDA &other) const;

    bool IsEqual() const;
    void IsEqual(bool value);
    bool IsNotEqual() const;
    void IsNotEqual(bool value);
    bool IsGreater() const;
    void IsGreater(bool value);
    bool IsGreaterOrEqual() const;
    void IsGreaterOrEqual(bool value);
    bool IsLess() const;
    void IsLess(bool value);
    bool IsLessOrEqual() const;
    void IsLessOrEqual(bool value);
    bool IsType(uint8_t Type) const;
    void SetType(uint8_t Type);

    bool IsNone() const;
    void IsNone(bool value);
    bool IsOr() const;
    void IsOr(bool value);
    bool IsUseAliases() const;
    void IsUseAliases(bool value);
    bool IsUseGlobal() const;
    void IsUseGlobal(bool value);
    bool IsUsePackData() const;
    void IsUsePackData(bool value);
    bool IsSwapSubject() const;
    void IsSwapSubject(bool value);
    bool IsFlagMask(uint8_t Mask, bool Exact = false) const;
    void SetFlagMask(uint8_t Mask);

    bool IsResultOnSubject() const;
    void IsResultOnSubject(bool value);
    bool IsResultOnTarget() const;
    void IsResultOnTarget(bool value);
    bool IsResultOnReference() const;
    void IsResultOnReference(bool value);
    bool IsResultOnCombatTarget() const;
    void IsResultOnCombatTarget(bool value);
    bool IsResultOnLinkedReference() const;
    void IsResultOnLinkedReference(bool value);
    bool IsResultOnQuestAlias() const;
    void IsResultOnQuestAlias(bool value);
    bool IsResultOnPackageData() const;
    void IsResultOnPackageData(bool value);
    bool IsResultOnEventData() const;
    void IsResultOnEventData(bool value);
    bool IsResultOnType(uint32_t Type) const;
    void SetResultOnType(uint32_t Type);
};
SIZE_CHECK(SKCTDA, 32);

struct SKCondition
{
    ReqSubRecord<SKCTDA> CTDA; // Condition
    StringRecord CIS1; // Parameter 1
    StringRecord CIS2; // Parameter 2

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const SKCondition &other) const;
    bool operator !=(const SKCondition &other) const;
};


struct SKEFIT
{
    float magnitude;
    uint32_t  area, duration;

    SKEFIT();
    ~SKEFIT();

    bool operator ==(const SKEFIT &other) const;
    bool operator !=(const SKEFIT &other) const;
};
SIZE_CHECK(SKEFIT, 12);

struct SKEffect
{
    ReqSimpleSubRecord<FORMID> EFID; //Effect ID
    ReqSubRecord<SKEFIT> EFIT; //Effect Data
    OrderedSparseArray<SKCondition *> CTDA; //Conditions

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const SKEffect &other) const;
    bool operator !=(const SKEffect &other) const;
};

struct GENATTACK
{
	struct ATTACKDATA
	{
		
        float damageMult;
        float attackChance;
        FORMID attackSpell;
        uint32_t flags;
        /*
		0x01 - Ignore Weapon
		0x02 - Bash Attack
		0x04 - Power Attack
		0x08 - Left Attack
		0x10 - Rotating Attack
        */

        float attackAngle;
        float strikeAngle;
        float stagger;
        FORMID attackType;
        float knockdown;
        float recoveryTime;
        float fatigueMult;


		bool operator ==(const ATTACKDATA &other) const;
		bool operator !=(const ATTACKDATA &other) const;
		
	};
    ReqSubRecord<ATTACKDATA> ATKD; // attack data
	StringRecord ATKE; // attack event

	void Write(FileWriter &writer);

    bool operator ==(const GENATTACK &other) const;
    bool operator !=(const GENATTACK &other) const;
};

struct GENPRKR
{
	FORMID  perk;
	uint8_t   rank, unused1[3];

	GENPRKR();
	~GENPRKR();

	void Write(FileWriter &writer);

	bool operator ==(const GENPRKR &other) const;
	bool operator !=(const GENPRKR &other) const;
};


struct XWCU {
	float x, y, z, unk;

	bool operator ==(const XWCU &other) const {
		return (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z);
	}
	bool operator !=(const XWCU &other) const {
		return !(*this == other);
	}
};

struct GenXLKR {
	FORMID kywd;
	FORMID formid;
	bool operator ==(const GenXLKR &other) const {
		return (this->kywd == other.kywd &&
			this->formid == other.formid);
	}
	bool operator !=(const GenXLKR &other) const {
		return !(*this == other);
	}
};

struct GenXLOC {
	uint32_t difficulty;
	FORMID key;
	uint32_t flags;
	uint8_t zeros[8];

	bool operator ==(const GenXLOC &other) const {
		return (this->difficulty == other.difficulty &&
			this->key == other.key &&
			this->flags == other.flags);
	}
	bool operator !=(const GenXLOC &other) const {
		return !(*this == other);
	}
};

/**
* When not lazy to wait for compilation - move to common
*/
struct COORDINATES {
	float x, y, z;
	bool operator ==(const COORDINATES &other) const {
		return (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z
			);
	}
	bool operator !=(const COORDINATES &other) const {
		return !(*this == other);
	}
};

struct ContainerItems {
	FORMID itemID;
	uint32_t itemCount;

	bool operator ==(const ContainerItems  &other) const {

		return (
			this->itemID == other.itemID &&
			this->itemCount == other.itemCount);

	}

	bool operator !=(const ContainerItems &other) const {
		return !(*this == other);
	}
};


struct EffectItem {
	float magnitude;
	uint32_t areaOfEffect;
	uint32_t duration;

	bool operator == (const EffectItem &other) const {
		return (
			this->magnitude == other.magnitude &&
			this->areaOfEffect == other.areaOfEffect &&
			this->duration == other.duration
		);
	}
	bool operator != (const EffectItem &other) const {
		return !(*this == other);
	}
};

struct SpellEffect {

	ReqSimpleSubRecord<FORMID> EFID;
	ReqSubRecord<EffectItem> EFIT;
	UnorderedSparseArray<SKCTDA *> CTDA;

	bool operator == (const SpellEffect &other) const {
		return (
			this->EFID == other.EFID &&
			this->EFIT == other.EFIT &&
			this->CTDA == other.CTDA 
			);
	}
	bool operator != (const SpellEffect &other) {
		return !(*this == other);
	}

	void Write(FileWriter &writer)
	{
		WRITE(EFID);
		WRITE(EFIT);
		WRITE(CTDA);
	}
};

} // namespace Sk
