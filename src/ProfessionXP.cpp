#include "ProfessionXP.h"

uint32 GetExperienceGain(Player* player, uint32 skillLevel)
{
    if (!sConfigMgr->GetOption<bool>("ProfessionXP.Enable", true))
    {
        return 0;
    }

    if(skillLevel == 0)
    {
        return 0;
    }

    uint32 effectiveLevel = skillLevel / 5;
    uint32 xpForLevel = sObjectMgr->GetXPForLevel(effectiveLevel);
    uint8 playerLevel = player->GetLevel();

    float xpRate = sConfigMgr->GetOption<float>("ProfessionXP.Rate", 0.05F);

    // a * b / c
    // a = XP Required to level at Effective Level
    // b = XP Rate (%) 0 - 1
    // c = The current player Level
    uint32 xpReward = static_cast<uint32>((xpForLevel * xpRate) / playerLevel);

    return xpReward;
}


void ProfessionXPPlayer::OnLogin(Player* player)
{
    bool announceOnLogin = sConfigMgr->GetOption<bool>("ProfessionXP.AnnounceOnLogin", true);
    bool enabled = sConfigMgr->GetOption<bool>("ProfessionXP.Enable", true);

    if(announceOnLogin && enabled)
    {
        ChatHandler(player->GetSession()).SendSysMessage("ProfessionXP is Enabled.");
    }
}

// When Craft is Completed
void ProfessionXPPlayer::OnUpdateCraftingSkill(Player* player, const SkillLineAbilityEntry* skill, uint32 currentLevel, uint32& gain)
{
    bool onCraft = sConfigMgr->GetOption<bool>("ProfessionXP.OnCraft", true);
    bool enabled = sConfigMgr->GetOption<bool>("ProfessionXP.Enable", true);

    if(onCraft && enabled)
    {
        uint32 xp = GetExperienceGain(player, currentLevel);
        player->GiveXP(xp, nullptr);
    }
}

// When Gather is Completed
void ProfessionXPPlayer::OnUpdateGatheringSkill(Player* player, uint32 skillID, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, uint32& gain)
{
    bool onGather = sConfigMgr->GetOption<bool>("ProfessionXP.OnGather", true);
    bool enabled = sConfigMgr->GetOption<bool>("ProfessionXP.Enable", true);

    if(onGather && enabled)
    {
        uint32 xp = GetExperienceGain(player, currentLevel);
        player->GiveXP(xp, nullptr);
    }  
}

// When Fishing is Completed
bool ProfessionXPPlayer::OnUpdateFishingSkill(Player* player, int32 skill, int32 zoneSkill, int32 chance, int32 roll)
{
    bool onFish = sConfigMgr->GetOption<bool>("ProfessionXP.OnFish", true);
    bool enabled = sConfigMgr->GetOption<bool>("ProfessionXP.Enable", true);

    if(onFish && enabled)
    {
        uint32 xp = GetExperienceGain(player, skill);
        player->GiveXP(xp, nullptr);
    }

    return true;
}