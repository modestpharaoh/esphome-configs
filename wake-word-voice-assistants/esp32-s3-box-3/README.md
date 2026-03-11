# ESP32-S3-BOX-3 with Arabic Support

This project provides a working example of how to render Arabic text on the ESP32-S3 Box 3 display using ESPHome. Since ESPHome does not natively support complex text shaping or Right-to-Left (RTL) text rendering, a custom C++ shaper is used.

## How the Arabic Shaper Works

Arabic characters change their shape depending on their position in a word (Isolated, Initial, Medial, or Final). Additionally, Arabic is written from right to left. The solution implemented here addresses both challenges.

### 1. Custom C++ Header (`arabic_shaper.h`)

The core logic resides in `arabic_shaper.h`. It performs the following steps:

- **Character Mapping**: It maps standard Arabic Unicode characters (U+0621 to U+064A) to their corresponding positional glyphs in the **Arabic Presentation Forms-B** block (U+FE70 to U+FEFF).
- **Contextual Shaping**: For each character, the shaper examines its immediate neighbors (skipping diacritics/harakat) to determine if it should use the Initial, Medial, Final, or Isolated form based on the character's connectivity properties.
- **Ligature Support**: It specifically handles the `Lam-Alef` (لأ, لإ, لآ, لا) ligatures, which are mandatory in Arabic script.
- **RTL Reversal**: Because most ESPHome display drivers render text from left to right (LTR), the shaper reverses the sequence of shaped characters. This ensures that when ESPHome draws them LTR, they appear in the correct RTL order on the screen.
- **UTF-8 Management**: The shaper decodes the input UTF-8 string into Unicode codepoints, processes them, and encodes the result back into a UTF-8 string that ESPHome can handle.

### 2. ESPHome Configuration (`esp32-s3-box-3-with-arabic-support.yaml`)

The YAML configuration integrates the shaper into the ESPHome environment:

- **Included Header**: The `arabic_shaper.h` file is included in the `esphome:` section:
  ```yaml
  esphome:
    includes:
      - arabic_shaper.h
  ```
- **Font Configuration**: To display the shaped characters, the font must include the **Arabic Presentation Forms-B** range. This is achieved by specifying the custom glyphs and using a compatible font like `Noto Sans Arabic`:
  ```yaml
  substitutions:
    arabic_glyphs: 'ﹰﹱﹲﹳﹴﹶﹷﹸﹹﹺﹻﹼﹽﹾﹿﺀﺁﺂﺃﺄﺅﺆﺇﺈﺉﺊﺋﺌﺍﺎﺏﺐﺑﺒﺓﺔﺕﺖﺗﺘﺙﺚﺛﺜﺝﺞﺟﺠﺡﺢﺣﺤﺥﺦﺧﺨﺩﺪﺫﺬﺭﺮﺯﺯﺱﺲﺳﺴﺵﺶﺷﺸﺹﺺﺻﺼﺽﺾﺿﻀﻁﻂﻃﻄﻅﻆﻇﻈﻉﻊﻋﻌﻍﻎﻏﻐﻑﻒﻓﻔﻕﻖﻗﻘﻙﻚﻛﻜﻝﻞﻟﻠﻡﻢﻣﻤﻥﻦﻧﻨﻩﻪﻫﻬﻭﻮﻯﻰﻱﻲﻳﻴﻵﻶﻷﻸﻹﻺﻻﻼ'

  font:
    - file:
        type: gfonts
        family: Noto Sans Arabic
      glyphs:
        - ${arabic_glyphs}
      glyphsets:
        - GF_Arabic_Core
  ```
- **Processing Logic**: Whenever the `text_request` or `text_response` sensors receive new text, a lambda function checks if it contains Arabic characters. If it does, it passes the text through `shape_arabic_and_reverse()` before displaying it.

## Benefits
- **Correct Connectivity**: Letters connect to each other naturally as they would in printed Arabic.
- **Correct Direction**: Text flows from right to left.
- **Minimal Overhead**: The lightweight C++ implementation runs efficiently on the ESP32-S3.

## Usage
Simply use the `esp32-s3-box-3-with-arabic-support.yaml` as your base configuration and ensure `arabic_shaper.h` is in the same directory. Any Arabic text assigned to the designated text sensors will be automatically shaped and reversed for the display.
