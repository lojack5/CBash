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
*  David "Dienes" Tynan
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

namespace Sk
{
    
    class NPC_Record : public TES5Record // Non-Player Character (Actor)
    {
    private:
        enum fields
        {
            fIdentifier = 0,
            // fSize, handled internally
            fMajorFlags,
            fFormID,
            fVersionControl,
            fFormVersion,
            fVersionControl2,
            fEDIS,
            // fVmad, not availible to API
            fOBND,
            fACBS,
            fFactions,
            fDeathItem


        };
        enum FlagFlags
        {
            fFemale                     = 0x00000001,
            fEssential                  = 0x00000002,
            fIsCharGenFacePreset        = 0x00000004,
            fRespawn                    = 0x00000008,
            fAutocalcStats              = 0x00000010,
            fUnique                     = 0x00000020,
            fDoesntAffectStealthMeter   = 0x00000040,
            fPCLevelMult                = 0x00000080,
            fUseTemplate                = 0x00000100,
            fUnknown9                   = 0x00000200,
            fUnknown10                  = 0x00000400,
            fProtected                  = 0x00000800,
            fUnknown12                  = 0x00001000,
            fUnknown13                  = 0x00002000,
            fSummonable                 = 0x00004000,
            fUnknown15                  = 0x00008000,
            fDoesntBleed                = 0x00010000,
            fUnknown17                  = 0x00020000,
            fBleedoutOverride           = 0x00040000,
            fOppositeGenderAnims        = 0x00080000,
            fSimpleActor                = 0x00100000,
            fLoopedscript               = 0x00200000,
            fUnknown22                  = 0x00400000,
            fUnknown23                  = 0x00800000,
            fUnknown24                  = 0x01000000,
            fUnknown25                  = 0x02000000,
            fUnknown26                  = 0x04000000,
            fUnknown27                  = 0x08000000,
            fLoopedAudio                = 0x10000000,
            fIsGhost                    = 0x20000000,
            fUnknown30                  = 0x40000000,
            fInvulnerable               = 0x80000000
        };
        enum TemplateFlags
        {
            fUseTraits          = 0x0001,
            fUseStats           = 0x0002,
            fUseFactions        = 0x0004,
            fUseSpellList       = 0x0008,
            fUseAIData          = 0x0010,
            fUseAIPackages      = 0x0020,
            fUseModelAnimation  = 0x0040,
            fUseBaseData        = 0x0080,
            fUseInventory       = 0x0100,
            fUseScript          = 0x0200,
            fUseDefPackList     = 0x0400,
            fUseAttackData      = 0x0800,
            fUseKeywords        = 0x1000
        };
        enum aggressionTypes
        {
            eUnaggressive = 0,
            eAggressive,
            eVeryAggressive,
            eFrenzied
        };

        enum confidenceTypes
        {
            eCowardly = 0,
            eCautious,
            eAverage,
            eBrave,
            eFoolhardy
        };

        enum responsibilityTypes
        {
            eAnyCrime = 0,
            eViolenceAgainstEnemies,
            ePropertyCrimeOnly,
            eNoCrime
        };

        enum moodTypes
        {
            eNeutral = 0,
            eAfraid,
            eAnnoyed,
            eCocky,
            eDrugged,
            ePleasant,
            eAngry,
            eSad
        };

        enum assistanceTypes
        {
            eHelpsNobody = 0,
            eHelpsAllies,
            eHelpsFriendsAndAllies
        };

        struct SKAIDT
        {
            uint8_t   aggression, confidence, energyLevel, responsibility, mood, assistance;
			uint8_t agroRadiusBehavior, unknown;
			uint32_t warn, warnAttack, attack;
			enum agroRadiusBehaviorTypes
			{
				eAggroRadiusBehaviorFalse = 0x00,
				eAggroRadiusBehaviorTrue = 0x01
			};

            SKAIDT();
            ~SKAIDT();

            bool operator ==(const SKAIDT &other) const;
            bool operator !=(const SKAIDT &other) const;
		};
        struct SKDNAM
        {
            // skill values
            int8_t OneHanded, TwoHanded, Marksman, Block, Smithing, HeavyArmor,
                LightArmor, Pickpocket, Lockpicking, Sneak, Alchemy, Speechcraft,
                Alteration, Conjuration, Destruction, Illusion, Restoration, Enchanting;
            //skill offsets
            int8_t OneHandedOff, TwoHandedOff, MarksmanOff, BlockOff, SmithingOff, HeavyArmorOff,
                LightArmorOff, PickpocketOff, LockpickingOff, SneakOff, AlchemyOff, SpeechcraftOff,
                AlterationOff, ConjurationOff, DestructionOff, IllusionOff, RestorationOff, EnchantingOff;
            uint16_t health, magicka, stamina; // calculated value if auto calculate is set
            uint16_t unused1;
            float farAwayModelDistance;
            uint8_t gearedUpWeapons;
            uint8_t unused2[3];

			SKDNAM();
			~SKDNAM();

			bool operator ==(const SKDNAM &other) const;
			bool operator !=(const SKDNAM &other) const;
        };
        struct SOUNDPAIR {
            ReqSubRecord<FORMID> CSDI; // sound form
            ReqSubRecord<uint8_t> CSDC; // sound chance

			bool operator ==(const SOUNDPAIR &other) const;
			bool operator !=(const SOUNDPAIR &other) const;
        };
        struct SOUNDPACK
        {
            enum SoundLocation
            {
                eLeftFoot = 0,
                eRightFoot,
                eLeftBackFoot,
                eRightBackFoot,
                eIdle,
                eAware,
                eAttack,
                eHit,
                eDeath,
                eWeapon,
                eMovementLoop,
                eConsciousLoop,
                eAuxiliary1,
                eAuxiliary2,
                eAuxiliary3,
                eAuxiliary4,
                eAuxiliary5,
                eAuxiliary6,
                eAuxiliary7,
                eAuxiliary8,
                eJump,
                ePlayRandomLoop
            };
            
			bool operator ==(const SOUNDPACK &other) const;
			bool operator !=(const SOUNDPACK &other) const;

            ReqSimpleSubRecord<uint32_t> soundLocation;
            UnorderedSparseArray<SOUNDPAIR *> sounds;
        };


        struct QNAMTRIPLE
        {
            float red;
            float green;
            float blue;

			bool operator ==(const QNAMTRIPLE &other) const;
			bool operator !=(const QNAMTRIPLE &other) const;
        };
        struct FACEMORPH
        {
            float NoseLongShort;
            float NoseUpDown;
            float JawUpDown;
            float JawNarrowWide;
            float JawFarwardBack;
            float CheeksUpDown;
            float CheeksFarwardBack;
            float EyesUpDown;
            float EyesInOut;
            float BrowsUpDown;
            float BrowsInOut;
            float BrowsFarwardBack;
            float LipsUpDown;
            float LipsInOut;
            float ChinNarrowWide;
            float ChinUpDown;
            float ChinUnderbiteOverbite;
            float EyesFarwardBack;
            float Unknown;

			bool operator ==(const FACEMORPH &other) const;
			bool operator !=(const FACEMORPH &other) const;
        };

        struct FACEPARTS
        {
            uint32_t nose;
            int32_t unknown;
            uint32_t eyes;
            uint32_t mouth;

			bool operator ==(const FACEPARTS &other) const;
			bool operator !=(const FACEPARTS &other) const;
        };

        struct TINTLAYER
        {
            struct TINTCOLORS
            {
                uint8_t red;
                uint8_t green;
                uint8_t blue;
                uint8_t alpha;
				

				bool operator ==(const TINTCOLORS &other) const;
				bool operator !=(const TINTCOLORS &other) const;

				TINTCOLORS();
				~TINTCOLORS();
			};

            ReqSimpleSubRecord<uint16_t> TINI; // tint index
            ReqSubRecord<TINTCOLORS> TINC;
            ReqSimpleSubRecord<uint32_t> TINV; // Interpolation Value * 100
            ReqSimpleSubRecord<int16_t> TIAS; // preset

			void Write(FileWriter &writer);

			bool operator ==(const TINTLAYER &other) const;
			bool operator !=(const TINTLAYER &other) const;
		};

    public:
        StringRecord EDID; //Editor ID
        VMADRecord VMAD; // Virtual Machind Data
        ReqSubRecord<GENOBND> OBND; // Object Bounds
        ReqSubRecord<TES5ACBS> ACBS;  // configuration
        UnorderedSparseArray<GENSNAM *> SNAM; // factions
        OptSimpleSubRecord<FORMID> INAM; //death item LVLI
        OptSimpleSubRecord<FORMID> VTCK; // voice VTYP
        OptSimpleSubRecord<FORMID> TPLT; // template NPC_ or LVLN
        OptSimpleSubRecord<FORMID> RNAM; // race RACE
        // ignored - SPCT spell count
        OptCounted<UnorderedSparseArray<FORMID>, int32_t, REV32(SPCT)> SPLO; // Actor effects
        OptSubRecord<SKDESTRUCT> Destructable; // destructable
        OptSimpleSubRecord<FORMID> WNAM; // skin ARMO
        OptSimpleSubRecord<FORMID> ANAM; // far away model
        OptSimpleSubRecord<FORMID> ATKR; // attack race
        UnorderedSparseArray<GENATTACK*> attacks; // attacks
        OptSimpleSubRecord<FORMID> SPOR; // spectator override packages FLST
        OptSimpleSubRecord<FORMID> OCOR; // Observe dead body override packages FLST
        OptSimpleSubRecord<FORMID> GWOR; // Guard warn override package FLST
        OptSimpleSubRecord<FORMID> ECOR; // Combat override package FLST
        // ignored - PRKZ perk count 
        OptCounted<UnorderedSparseArray<GENPRKR *>, uint32_t, REV32(PRKZ)> PRKR; // perks
        // ignored - COCT item count
        OptCounted<UnorderedSparseArray<GENCNTO *>, int32_t, REV32(COCT)> CNTO; // items
        ReqSubRecord<SKAIDT> AIDT; // AI data
        UnorderedSparseArray<FORMID> PKID; // packages
        // ignored - KSIZ keyword count
        OptCounted<OrderedPackedArray<FORMID>, uint32_t, REV32(KSIZ)> KWDA; // Keywords
        ReqSubRecord<FORMID> CNAM; // class
        LStringRecord FULL; // full name
        LStringRecord SHRT; // short name
        // Data - 0 size
        OptSubRecord<SKDNAM> DNAM; // actor skills
        UnorderedSparseArray<FORMID> PNAM; // headparts - HDPT
        OptSimpleSubRecord<FORMID> HCLF; // hair color - CLFM
        OptSimpleSubRecord<FORMID> ZNAM; // combat style - CSTY
        OptSimpleSubRecord<FORMID> GNAM; // gift filter - FLST
        ReqSubRecord<int16_t> NAM5; // unknown?
        ReqSimpleFloatSubRecord<> NAM6; // Height
        ReqSimpleFloatSubRecord<> NAM7; // Weight
        ReqSimpleSubRecord<int> NAM8; // sound level - enum 'Loud','Normal','Silent','Very Loud'
        UnorderedSparseArray<SOUNDPACK *> CSDT; // sound package - not present if CSCR exists
        OptSimpleSubRecord<FORMID> CSCR; // Inherits Sounds From - NPC_
        OptSimpleSubRecord<FORMID> DOFT; // default outfit - OTFT
        OptSimpleSubRecord<FORMID> SOFT; // sleep outfit - OTFT
        OptSimpleSubRecord<FORMID> DPLT; // default package list - FLST
        OptSimpleSubRecord<FORMID> CRIF; // crime faction - FACT
        OptSimpleSubRecord<FORMID> FTST; // face textures - TXST
        OptSubRecord<QNAMTRIPLE> QNAM; // texture lighting
        OptSubRecord<FACEMORPH> NAM9; // facemorph
        OptSubRecord<FACEPARTS> NAMA; // faceparts
        UnorderedSparseArray<TINTLAYER *> TintLayers; // tint layers

        NPC_Record(unsigned char *_recData = NULL);
        NPC_Record(NPC_Record *srcRecord);
        ~NPC_Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool IsFemale();
        void IsFemale(bool value);
        bool IsEssential();
        void IsEssential(bool value);
        bool IsIsCharGenFacePreset();
        void IsIsCharGenFacePreset(bool value);
        bool IsRespawn();
        void IsRespawn(bool value);
        bool IsAutocalcStats();
        void IsAutocalcStats(bool value);
        bool IsUnique();
        void IsUnique(bool value);
        bool IsDoesntAffectStealthMeter();
        void IsDoesntAffectStealthMeter(bool value);
        bool IsPCLevelMult();
        void IsPCLevelMult(bool value);
        bool IsUseTemplate();
        void IsUseTemplate(bool value);
        bool IsUnknown9();
        void IsUnknown9(bool value);
        bool IsUnknown10();
        void IsUnknown10(bool value);
        bool IsProtected();
        void IsProtected(bool value);
        bool IsUnknown12();
        void IsUnknown12(bool value);
        bool IsUnknown13();
        void IsUnknown13(bool value);
        bool IsSummonable();
        void IsSummonable(bool value);
        bool IsUnknown15();
        void IsUnknown15(bool value);
        bool IsDoesntBleed();
        void IsDoesntBleed(bool value);
        bool IsUnknown17();
        void IsUnknown17(bool value);
        bool IsBleedoutOverride();
        void IsBleedoutOverride(bool value);
        bool IsOppositeGenderAnims();
        void IsOppositeGenderAnims(bool value);
        bool IsSimpleActor();
        void IsSimpleActor(bool value);
        bool IsLoopedscript();
        void IsLoopedscript(bool value);
        bool IsUnknown22();
        void IsUnknown22(bool value);
        bool IsUnknown23();
        void IsUnknown23(bool value);
        bool IsUnknown24();
        void IsUnknown24(bool value);
        bool IsUnknown25();
        void IsUnknown25(bool value);
        bool IsUnknown26();
        void IsUnknown26(bool value);
        bool IsUnknown27();
        void IsUnknown27(bool value);
        bool IsLoopedAudio();
        void IsLoopedAudio(bool value);
        bool IsIsGhost();
        void IsIsGhost(bool value);
        bool IsUnknown30();
        void IsUnknown30(bool value);
        bool IsInvulnerable();
        void IsInvulnerable(bool value);

        bool   IsFlagMask(uint32_t Mask, bool Exact = false) const;
        void   SetFlagMask(uint32_t Mask);

		uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute = 0);
		void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues = NULL);
		bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue = NULL, uint32_t ArraySize = 0);
		void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk = false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

        bool operator ==(const NPC_Record &other) const;
        bool operator !=(const NPC_Record &other) const;
        bool equals(Record *other);


    };
} // namespace Sk