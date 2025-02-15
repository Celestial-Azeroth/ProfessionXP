#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

uint32 GetExperienceGain(Player* player, uint32 skillLevel);

// Add player scripts
class ProfessionXPPlayer : public PlayerScript
{
    public:
        ProfessionXPPlayer() : PlayerScript("ProfessionXPPlayer") { }

        void OnLogin(Player* player) override;

        void OnUpdateCraftingSkill(Player* player, const SkillLineAbilityEntry* skill, uint32 currentLevel, uint32& gain) override;
        void OnUpdateGatheringSkill(Player* player, uint32 skillID, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, uint32& gain) override;
        bool OnUpdateFishingSkill(Player* player, int32 skill, int32 zoneSkill, int32 chance, int32 roll) override;
    };

// Add all scripts in one
void AddProfessionXPScripts()
{
    new ProfessionXPPlayer();
}
