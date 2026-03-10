// arabic_shaper.h a library to help write arabic letters correctly
// on ESP display
#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct ArabicGlyph {
    uint32_t iso;
    uint32_t fin;
    uint32_t ini;
    uint32_t med;
};

// Mapping from 0x0621 to 0x064A
static const ArabicGlyph ARABIC_TABLE[] = {
    {0xFE80, 0x0000, 0x0000, 0x0000}, // 0x621: Hamza
    {0xFE81, 0xFE82, 0x0000, 0x0000}, // 0x622: Alef with Madda
    {0xFE83, 0xFE84, 0x0000, 0x0000}, // 0x623: Alef with Hamza Above
    {0xFE85, 0xFE86, 0x0000, 0x0000}, // 0x624: Waw with Hamza Above
    {0xFE87, 0xFE88, 0x0000, 0x0000}, // 0x625: Alef with Hamza Below
    {0xFE89, 0xFE8A, 0xFE8B, 0xFE8C}, // 0x626: Yeh with Hamza Above
    {0xFE8D, 0xFE8E, 0x0000, 0x0000}, // 0x627: Alef
    {0xFE8F, 0xFE90, 0xFE91, 0xFE92}, // 0x628: Beh
    {0xFE93, 0xFE94, 0x0000, 0x0000}, // 0x629: Teh Marbuta
    {0xFE95, 0xFE96, 0xFE97, 0xFE98}, // 0x62A: Teh
    {0xFE99, 0xFE9A, 0xFE9B, 0xFE9C}, // 0x62B: Theh
    {0xFE9D, 0xFE9E, 0xFE9F, 0xFEA0}, // 0x62C: Jeem
    {0xFEA1, 0xFEA2, 0xFEA3, 0xFEA4}, // 0x62D: Hah
    {0xFEA5, 0xFEA6, 0xFEA7, 0xFEA8}, // 0x62E: Khah
    {0xFEA9, 0xFEAA, 0x0000, 0x0000}, // 0x62F: Dal
    {0xFEAB, 0xFEAC, 0x0000, 0x0000}, // 0x630: Thal
    {0xFEAD, 0xFEAE, 0x0000, 0x0000}, // 0x631: Reh
    {0xFEAF, 0xFEB0, 0x0000, 0x0000}, // 0x632: Zain
    {0xFEB1, 0xFEB2, 0xFEB3, 0xFEB4}, // 0x633: Seen
    {0xFEB5, 0xFEB6, 0xFEB7, 0xFEB8}, // 0x634: Sheen
    {0xFEB9, 0xFEBA, 0xFEBB, 0xFEBC}, // 0x635: Sad
    {0xFEBD, 0xFEBE, 0xFEBF, 0xFEC0}, // 0x636: Dad
    {0xFEC1, 0xFEC2, 0xFEC3, 0xFEC4}, // 0x637: Tah
    {0xFEC5, 0xFEC6, 0xFEC7, 0xFEC8}, // 0x638: Zah
    {0xFEC9, 0xFECA, 0xFECB, 0xFECC}, // 0x639: Ain
    {0xFECD, 0xFECE, 0xFECF, 0xFED0}, // 0x63A: Ghain
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x63B: (not used here)
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x63C: (not used here)
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x63D: (not used here)
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x63E: (not used here)
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x63F: (not used here)
    {0x0000, 0x0000, 0x0000, 0x0000}, // 0x640: Tatweel (not letter)
    {0xFED1, 0xFED2, 0xFED3, 0xFED4}, // 0x641: Feh
    {0xFED5, 0xFED6, 0xFED7, 0xFED8}, // 0x642: Qaf
    {0xFED9, 0xFEDA, 0xFEDB, 0xFEDC}, // 0x643: Kaf
    {0xFEDD, 0xFEDE, 0xFEDF, 0xFEE0}, // 0x644: Lam
    {0xFEE1, 0xFEE2, 0xFEE3, 0xFEE4}, // 0x645: Meem
    {0xFEE5, 0xFEE6, 0xFEE7, 0xFEE8}, // 0x646: Noon
    {0xFEE9, 0xFEEA, 0xFEEB, 0xFEEC}, // 0x647: Heh
    {0xFEED, 0xFEEE, 0x0000, 0x0000}, // 0x648: Waw
    {0xFEEF, 0xFEF0, 0x0000, 0x0000}, // 0x649: Alef Maksura
    {0xFEF1, 0xFEF2, 0xFEF3, 0xFEF4}  // 0x64A: Yeh
};

inline bool is_arabic_char(uint32_t cp) {
    return (cp >= 0x0621 && cp <= 0x064A);
}

inline bool is_arabic_shaping_char(uint32_t cp) {
    if (!is_arabic_char(cp)) return false;
    ArabicGlyph g = ARABIC_TABLE[cp - 0x0621];
    return g.iso != 0;
}

inline bool connects_to_left(uint32_t cp) {
    if (!is_arabic_char(cp)) return false;
    ArabicGlyph g = ARABIC_TABLE[cp - 0x0621];
    return g.ini != 0 || g.med != 0;
}

inline bool is_transparent(uint32_t cp) {
    // Diacritics/Harakat are transparent to shaping
    return (cp >= 0x064B && cp <= 0x065F) || cp == 0x0670;
}

inline std::string shape_arabic_and_reverse(const std::string& input) {
    std::vector<uint32_t> cps;
    size_t i = 0;
    while (i < input.size()) {
        uint32_t cp = 0;
        int len = 1;
        uint8_t c = (uint8_t)input[i];
        if (c < 0x80) { cp = c; len = 1; }
        else if ((c & 0xE0) == 0xC0) { cp = c & 0x1F; len = 2; }
        else if ((c & 0xF0) == 0xE0) { cp = c & 0x0F; len = 3; }
        else if ((c & 0xF8) == 0xF0) { cp = c & 0x07; len = 4; }
        for (int j = 1; j < len && (i + j) < input.size(); j++)
            cp = (cp << 6) | ((uint8_t)input[i + j] & 0x3F);
        cps.push_back(cp);
        i += len;
    }

    std::vector<uint32_t> shaped;
    for (size_t i = 0; i < cps.size(); i++) {
        uint32_t c = cps[i];

        if (is_arabic_shaping_char(c)) {
            // Find right neighbour (skip transparent diacritics)
            bool right_connects = false;
            for (int j = (int)i - 1; j >= 0; j--) {
                if (is_transparent(cps[j])) continue;
                if (connects_to_left(cps[j])) right_connects = true;
                break;
            }

            // Find left neighbour (skip transparent diacritics)
            bool left_connects = false;
            size_t next_char_idx = i + 1;
            for (size_t j = i + 1; j < cps.size(); j++) {
                if (is_transparent(cps[j])) continue;
                if (is_arabic_shaping_char(cps[j])) {
                    left_connects = true;
                    next_char_idx = j;
                }
                break;
            }

            // basic replacement for LAAM ALEF ligature
            if (c == 0x0644 && left_connects) { // Lam
                uint32_t next = cps[next_char_idx];
                if (next == 0x0622 || next == 0x0623 || next == 0x0625 || next == 0x0627) { // Alef variants
                    uint32_t lig = 0;
                    if (next == 0x0622) lig = right_connects ? 0xFEF6 : 0xFEF5; // Lam with Alef Madda Above
                    else if (next == 0x0623) lig = right_connects ? 0xFEF8 : 0xFEF7; // Lam with Alef Hamza Above
                    else if (next == 0x0625) lig = right_connects ? 0xFEFA : 0xFEF9; // Lam with Alef Hamza Below
                    else if (next == 0x0627) lig = right_connects ? 0xFEFC : 0xFEFB; // Lam with Alef
                    shaped.push_back(lig);
                    
                    // Push any transparents between Lam and Alef
                    for(size_t j = i + 1; j < next_char_idx; j++) {
                        shaped.push_back(cps[j]);
                    }
                    
                    i = next_char_idx; // skip the Alef we just merged
                    continue;
                }
            }

            ArabicGlyph g = ARABIC_TABLE[c - 0x0621];
            uint32_t out = c;
            
            // To connect left as well, the letter itself (c) must be able to connect left (have Med/Ini forms)
            bool can_connect_left = (g.ini != 0 || g.med != 0);
            left_connects = left_connects && can_connect_left;

            if (right_connects && left_connects && g.med) out = g.med;
            else if (right_connects && !left_connects && g.fin) out = g.fin;
            else if (!right_connects && left_connects && g.ini) out = g.ini;
            else if (g.iso) out = g.iso;
            shaped.push_back(out);
        } else {
            shaped.push_back(c);
        }
    }

    std::string result = "";
    // reverse and encode
    for (int i = shaped.size() - 1; i >= 0; i--) {
        uint32_t cp = shaped[i];
        if (cp < 0x80) {
            result += (char)cp;
        } else if (cp < 0x800) {
            result += (char)(0xC0 | (cp >> 6));
            result += (char)(0x80 | (cp & 0x3F));
        } else if (cp < 0x10000) {
            result += (char)(0xE0 | (cp >> 12));
            result += (char)(0x80 | ((cp >> 6) & 0x3F));
            result += (char)(0x80 | (cp & 0x3F));
        } else {
            result += (char)(0xF0 | (cp >> 18));
            result += (char)(0x80 | ((cp >> 12) & 0x3F));
            result += (char)(0x80 | ((cp >> 6) & 0x3F));
            result += (char)(0x80 | (cp & 0x3F));
        }
    }

    return result;
}
