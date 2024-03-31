#include <stdlib.h>    // Standard Library: General purpose functions, including dynamic memory allocation and random number generation.
#include <stdio.h>     // Standard Input/Output: Functions for reading and writing to the console.
#include <stdbool.h>   // Standard Boolean: Defines the bool type and true/false constants.
#include <string.h>    // String Library: Functions for manipulating strings.
#include <ctype.h>     // Character Type: Functions for character handling, like checking if a character is alphanumeric.
#include <unistd.h>    // Unix Standard: Functions related to system calls, including sleep().
#include <time.h>      // Time Library: Functions for working with date and time.
#include <float.h>     // Floating Point Library: Functions for floating point math.
#include <math.h>      // Math Library: Functions for mathematical operations.

/* Terminal stuff (UI) */
#define CLEAR_TERMINAL "\033[2J\033[1;1H"

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"

/* Generally used constants */
#define ROW 3
#define COLUMN 3

/****************************************************/
/*******|         Project Specifics          |*******/
/****************************************************/

/* Grid sizes */
#define DIAG 3

#define DEFAULT 687084

/* Types */
typedef struct Grid
{
    char grid[ROW][COLUMN];
} Grid;

typedef char List[ROW + 1][COLUMN + 1];

typedef char *gridBlocks[3][9];

typedef char gamertag[46];

/* Constants */
const List LETTERS = {
    {'A', 'B', 'C', 'Z'},
    {'D', 'E', 'F', 'Z'},
    {'G', 'H', 'I', 'Z'},
    {'Z', 'Z', 'Z', 'Z'}};

enum Players
{
    P1 = 1,
    P2 = 2,
    BOT = 2,
    DRAW = 0
};

enum error_codes /* There is a logic to it, try to fint it I'll give you a cookie :D */
{
    INPUT_TOO_LONG = 738476,
    NON_INT_INPUT = 787373,
    INT_OUT_OF_RANGE = 737982,
    NON_CHAR_INPUT = 786773,
    CHAR_INPUT_UNRECONIZED = 677385,
    CELL_TAKEN = 678475,
    GRID_TAKEN = 718475,
    PLAYER_ID = 807368,

    DEBUG = 686671,
    UNEXPECTED = 856984
};

enum choices /* Same logic here for DEFAULT :) */
{
    RULES = 1,
    MATCH_1P = 2,
    MATCH_2P = 3,
    EXIT = 0,
    SECRET = 836784
};

enum difficulties
{
    EASY = 1,
    MEDIUM = 2,
    HARD = 3,
    MENU = 0
};

/*-- For the random names --*/
const char *vowels[6] = {"a", "e", "i", "o", "u", "y"};
const char *consonant[20] = {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "z"};

#define nbOfMemeNames 23
const char *memeNames[23] = {"Pomni", "Xddcc", "PvZGamer", "ElGato", "RickAstley", "BadLuckBrian", "GoodGuyGreg", "Fred", "ForeverAlone", "Pepega", "Area51Raider", "BitcoinMiner", "TheCakeIsALie", "JohnCena", "E", "Shrek", "StonksMan", "Karen", "Shaggy", "CrazyFrog", "LittleRedShit", "LampLover", "UsernameWasTaken"};

#define nbPrefixes 159
const char *Prefixes[nbPrefixes] = {"1337", "Aggro", "Alpha", "Altered", "Ancient", "Angel", "Anonymous", "Aqua", "Arcane", "Ashen", "Assault", "Atomic", "Awakened", "Bad", "Baneful", "Bio", "Bionic", "Black", "Blade", "Blessed", "Blood", "Bloody", "Boosted", "Brutal", "Buffed", "Carnage", "Catastrophic", "Chaos", "Charged", "Chrome", "Chrono", "Combo", "Concealed", "Consumptive", "Corrupted", "Creeping", "Crimson", "Cryptic", "Cunning", "Cyber", "Dark", "Darth", "Dead", "Decimate", "Deep", "Destructive", "Devil", "Diamond", "Divine", "Doom", "Dormant", "Draconic", "Dynamic", "Elder", "Electro", "Elite", "Emerald", "Enemy", "Eon", "Epic", "Eradicate", "Evanescent", "Exiled", "Fallen", "Fatal", "Fire", "First", "Frost", "Frozen", "Gold", "Gosu", "Grim", "Guerilla", "Hardcore", "Hate", "Hazardous", "Hidden", "Holy", "Icy", "Imba", "Incendiary", "Incognito", "Infinite", "Invisible", "Iron", "Killer", "Last", "Leeroy", "Lone", "Mad", "Majestic", "Malefic", "Malevolent", "Malignant", "Master", "Menacing", "Metal", "Mind", "Mirror", "Mist", "Mono", "Moon", "Murderous", "Mystic", "Nameless", "Necro", "Negative", "Neo", "Nightmare", "Nocturnal", "Occult", "Omnipotent", "Panic", "Pernicious", "Platinum", "Prime", "Psychic", "Quantum", "Radical", "Radient", "Rage", "Random", "Savage", "Secret", "Shadow", "Silver", "Sinister", "Sky", "Solar", "Solid", "Solitary", "Somber", "Soul", "Stealth", "Steel", "Storm", "Supernatural", "Swift", "Terror", "Toxic", "Tranquil", "Transcendent", "Treacherous", "True", "Twisted", "Uber", "Ultimate", "Undercover", "Unknowable", "Unpredictable", "Urban", "Veiled", "Venom", "Vindictive", "Virulent", "Warp", "Wicked", "Xeno", "Zero"};

#define nbMainName 232
const char *MainName[nbMainName] = {"Aegis", "Aether", "Agent", "Agitator", "Alias", "Archetype", "Archon", "Armor", "Arrow", "Arsenal", "Arsonist", "Assassin", "Assault", "Asylum", "Atonement", "Augur", "Aura", "Avenger", "Axiom", "Axon", "Battle", "Beast", "Beastmode", "Being", "Betrayal", "Blade", "Blaster", "Blaze", "Blood", "Boss", "Burn", "Cabal", "Cannon", "Captain", "Carnage", "Caster", "Cataclysm", "Catalyst", "Chaos", "Chief", "Child", "Chimera", "Clairvoyant", "Cloud", "Combat", "Commander", "Crypt", "Cut", "Cyborg", "Damage", "Death", "Deathmatch", "Decay", "Decay", "Demon", "Destruction", "Devil", "Divinity", "Doom", "Doppleganger", "Dragon", "Dragoon", "Dream", "Dynasty", "Edge", "Effect", "Elder", "Elixir", "Elysium", "Emperor", "Empire", "Enemy", "Enigma", "Entity", "Epidemic", "Equilibrium", "Equinox", "Eve", "Executioner", "Exekutioner", "Exodus", "Explosive", "Fatality", "Fate", "Fire", "Firebreath", "Flame", "Flux", "Focus", "Force", "Freak", "Frenzy", "Frost", "Fury", "Fusion", "Galaxy", "Genesis", "Ghost", "Glitch", "God", "Godmode", "Grenade", "Grimoire", "Guard", "Guardian", "Gun", "Hacker", "Haxxor", "Headshot", "Hell", "Hellion", "Hivemind", "Hunter", "Hysteria", "Impunity", "Inferno", "Intellect", "Juggernaut", "Kaos", "Killer", "Killswitch", "Legend", "Limit", "Lucifer", "Machete", "Machine", "Maelstrom", "Master", "Mercenary", "Mercy", "Mind", "Mine", "Monarch", "Monolith", "Mood", "Moon", "Nexus", "Night", "Nightmare", "Ninja", "Nuke", "Oath", "Obelisk", "Obliteration", "Oblivion", "Odyssey", "Omen", "Omnichrom", "Oracle", "Outlaw", "Overmind", "Pain", "Panic", "Panzer", "Paradox", "Paragon", "Partisan", "Planet", "Plasma", "Priest", "Prison", "Propaganda", "Prophet", "Psychosis", "Punishment", "Pwner", "Pyromaniac", "Quake", "Rachet", "Radical", "Raid", "Raider", "Rat", "Ray", "Razor", "Reaper", "Rebel", "Redshift", "Reflux", "Requiem", "Rhapsody", "Ringleader", "Rival", "Rogue", "Root", "Rush", "Sabotage", "Scream", "Seeker", "Seer", "Seizure", "Shade", "Shooter", "Sin", "Slash", "Slayer", "Sniper", "Snow", "Soul", "Space", "Spark", "Star", "Storm", "Strategy", "Stroke", "Tank", "Tempest", "Terror", "Thunder", "Titan", "Tornado", "Trigger", "Trinity", "Universe", "Vehicle", "Vengeance", "Venom", "Venus", "Visionary", "Void", "Voltage", "Voodoo", "Vortex", "Warlock", "Warrior", "Whisper", "Wing", "Wizard", "Wolf", "Zealot", "Zephyr", "Zone"};

#define nbFlaires 7
const char *Flairs[nbFlaires][2] = {{"xX", "Xx"}, {"<<", ">>"}, {"-=", "=-"}, {"-~", "~-"}, {"~*", "*~"}, {".:", ":."}, {"#*", "*#"}};

#define nbBotNames 15
const char *BotNames[nbBotNames] = {"NoviceBot", "SimpleAI", "BeginnerMind", "SoftSkillBot", "EasyGoAI", "AdaptiveLogic", "BalancedBrain", "IntermediateMind", "ModestMinds", "MiddleGroundAI", "ProdigyProcessor", "AdvancedAlgorithm", "ExpertMind", "HardcoreHeuristics", "EliteEngineAI"};
