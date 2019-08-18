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

namespace Ob
{
class SPELRecord : public Record
    {
    private:
        struct SPELSPIT
            {
            uint32_t  spellType, cost, levelType;
            uint8_t   flags, unused1[3];

            SPELSPIT();
            ~SPELSPIT();

            bool operator ==(const SPELSPIT &other) const;
            bool operator !=(const SPELSPIT &other) const;
            };

        enum eManualFixing {
            eBadScript = 0x0100C079
            };

        enum flagsFlags
            {
            fIsManualCost            = 0x00000001,
            fIsStartSpell            = 0x00000004,
            fIsSilenceImmune         = 0x0000000A,
            fIsAreaEffectIgnoresLOS  = 0x00000010,
            fIsScriptAlwaysApplies   = 0x00000020,
            fIsDisallowAbsorbReflect = 0x00000040,
            fIsTouchExplodesWOTarget = 0x00000080
            };

        enum eSpellType
            {
            eSpell       = 0,
            eDisease     = 1,
            ePower       = 2,
            eLesserPower = 3,
            eAbility     = 4,
            ePoison      = 5
            };

        enum eSpellLevel
            {
            eNovice     = 0,
            eApprentice = 1,
            eJourneyman = 2,
            eExpert     = 3,
            eMaster     = 4
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        ReqSubRecord<SPELSPIT> SPIT; //Data
        UnorderedSparseArray<GENEffect *> Effects; //Effects
        OptSubRecord<OBMEMAGIC> OBME; //OBME Extended Data

        SPELRecord(unsigned char *_recData=NULL);
        SPELRecord(SPELRecord *srcRecord);
        ~SPELRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsManualCost();
        void   IsManualCost(bool value);
        bool   IsStartSpell();
        void   IsStartSpell(bool value);
        bool   IsSilenceImmune();
        void   IsSilenceImmune(bool value);
        bool   IsAreaEffectIgnoresLOS();
        void   IsAreaEffectIgnoresLOS(bool value);
        bool   IsAEIgnoresLOS();
        void   IsAEIgnoresLOS(bool value);
        bool   IsScriptAlwaysApplies();
        void   IsScriptAlwaysApplies(bool value);
        bool   IsDisallowAbsorbReflect();
        void   IsDisallowAbsorbReflect(bool value);
        bool   IsDisallowAbsorb();
        void   IsDisallowAbsorb(bool value);
        bool   IsDisallowReflect();
        void   IsDisallowReflect(bool value);
        bool   IsTouchExplodesWOTarget();
        void   IsTouchExplodesWOTarget(bool value);
        bool   IsTouchExplodes();
        void   IsTouchExplodes(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        bool   IsSpell();
        void   IsSpell(bool value);
        bool   IsDisease();
        void   IsDisease(bool value);
        bool   IsPower();
        void   IsPower(bool value);
        bool   IsLesserPower();
        void   IsLesserPower(bool value);
        bool   IsAbility();
        void   IsAbility(bool value);
        bool   IsPoison();
        void   IsPoison(bool value);
        bool   IsType(uint32_t Type);
        void   SetType(uint32_t Type);

        bool   IsNovice();
        void   IsNovice(bool value);
        bool   IsApprentice();
        void   IsApprentice(bool value);
        bool   IsJourneyman();
        void   IsJourneyman(bool value);
        bool   IsExpert();
        void   IsExpert(bool value);
        bool   IsMaster();
        void   IsMaster(bool value);
        bool   IsLevel(uint32_t Type);
        void   SetLevel(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const SPELRecord &other) const;
        bool operator !=(const SPELRecord &other) const;
        bool equals(Record *other);
    };
}