/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 100 vteseq-n.gperf  */
/* Computed positions: -k'1,8,12,18' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 16 "vteseq-n.gperf"
struct vteseq_n_struct {
	int seq;
	VteTerminalSequenceHandler handler;
};
#include <string.h>
/* maximum key range = 118, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
vteseq_n_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129,  27, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129,   6,  21,   2,
       11,  35,  48,   5,   7,   6, 129,  50,  33,  15,
        2,   2,   3, 129,   3,   5,  19,  48,  21,   5,
      129,  29, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129, 129, 129, 129, 129,
      129, 129, 129, 129, 129, 129
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[17]];
      /*FALLTHROUGH*/
      case 17:
      case 16:
      case 15:
      case 14:
      case 13:
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
      case 10:
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

struct vteseq_n_pool_t
  {
    char vteseq_n_pool_str11[sizeof("index")];
    char vteseq_n_pool_str13[sizeof("next-line")];
    char vteseq_n_pool_str15[sizeof("reset-mode")];
    char vteseq_n_pool_str16[sizeof("reset-color")];
    char vteseq_n_pool_str17[sizeof("decset")];
    char vteseq_n_pool_str19[sizeof("save-cursor")];
    char vteseq_n_pool_str20[sizeof("soft-reset")];
    char vteseq_n_pool_str22[sizeof("change-color-st")];
    char vteseq_n_pool_str23[sizeof("change-color-bel")];
    char vteseq_n_pool_str24[sizeof("cursor-down")];
    char vteseq_n_pool_str25[sizeof("save-mode")];
    char vteseq_n_pool_str26[sizeof("tab-set")];
    char vteseq_n_pool_str27[sizeof("scroll-down")];
    char vteseq_n_pool_str31[sizeof("change-cursor-colors-st")];
    char vteseq_n_pool_str32[sizeof("change-cursor-colors-bel")];
    char vteseq_n_pool_str33[sizeof("reset-foreground-colors")];
    char vteseq_n_pool_str34[sizeof("tab-clear")];
    char vteseq_n_pool_str35[sizeof("set-scrolling-region")];
    char vteseq_n_pool_str36[sizeof("delete-characters")];
    char vteseq_n_pool_str37[sizeof("reset-background-colors")];
    char vteseq_n_pool_str38[sizeof("decreset")];
    char vteseq_n_pool_str39[sizeof("cursor-position")];
    char vteseq_n_pool_str40[sizeof("set-icon-title")];
    char vteseq_n_pool_str41[sizeof("cursor-character-absolute")];
    char vteseq_n_pool_str42[sizeof("set-scrolling-region-to-end")];
    char vteseq_n_pool_str43[sizeof("cursor-backward")];
    char vteseq_n_pool_str44[sizeof("window-manipulation")];
    char vteseq_n_pool_str45[sizeof("set-icon-and-window-title")];
    char vteseq_n_pool_str46[sizeof("set-scrolling-region-from-start")];
    char vteseq_n_pool_str47[sizeof("cursor-next-line")];
    char vteseq_n_pool_str48[sizeof("set-mode")];
    char vteseq_n_pool_str49[sizeof("restore-cursor")];
    char vteseq_n_pool_str50[sizeof("reset-highlight-foreground-colors")];
    char vteseq_n_pool_str51[sizeof("set-window-title")];
    char vteseq_n_pool_str52[sizeof("erase-in-line")];
    char vteseq_n_pool_str53[sizeof("screen-alignment-test")];
    char vteseq_n_pool_str54[sizeof("reset-highlight-background-colors")];
    char vteseq_n_pool_str55[sizeof("cursor-lower-left")];
    char vteseq_n_pool_str56[sizeof("insert-lines")];
    char vteseq_n_pool_str57[sizeof("return-terminal-id")];
    char vteseq_n_pool_str58[sizeof("erase-in-display")];
    char vteseq_n_pool_str59[sizeof("cursor-up")];
    char vteseq_n_pool_str60[sizeof("erase-characters")];
    char vteseq_n_pool_str61[sizeof("delete-lines")];
    char vteseq_n_pool_str62[sizeof("scroll-up")];
    char vteseq_n_pool_str63[sizeof("full-reset")];
    char vteseq_n_pool_str64[sizeof("line-position-absolute")];
    char vteseq_n_pool_str65[sizeof("cursor-back-tab")];
    char vteseq_n_pool_str66[sizeof("send-secondary-device-attributes")];
    char vteseq_n_pool_str67[sizeof("horizontal-and-vertical-position")];
    char vteseq_n_pool_str68[sizeof("character-position-absolute")];
    char vteseq_n_pool_str69[sizeof("return-terminal-status")];
    char vteseq_n_pool_str70[sizeof("cursor-forward")];
    char vteseq_n_pool_str71[sizeof("normal-keypad")];
    char vteseq_n_pool_str72[sizeof("send-primary-device-attributes")];
    char vteseq_n_pool_str73[sizeof("dec-device-status-report")];
    char vteseq_n_pool_str75[sizeof("request-terminal-parameters")];
    char vteseq_n_pool_str76[sizeof("reset-cursor-colors")];
    char vteseq_n_pool_str77[sizeof("restore-mode")];
    char vteseq_n_pool_str78[sizeof("reverse-index")];
    char vteseq_n_pool_str79[sizeof("set-current-directory-uri")];
    char vteseq_n_pool_str81[sizeof("application-keypad")];
    char vteseq_n_pool_str82[sizeof("change-background-colors-st")];
    char vteseq_n_pool_str83[sizeof("change-background-colors-bel")];
    char vteseq_n_pool_str86[sizeof("device-status-report")];
    char vteseq_n_pool_str87[sizeof("vertical-tab")];
    char vteseq_n_pool_str92[sizeof("form-feed")];
    char vteseq_n_pool_str94[sizeof("cursor-preceding-line")];
    char vteseq_n_pool_str95[sizeof("character-attributes")];
    char vteseq_n_pool_str98[sizeof("iso8859-1-character-set")];
    char vteseq_n_pool_str100[sizeof("change-highlight-background-colors-st")];
    char vteseq_n_pool_str101[sizeof("change-highlight-background-colors-bel")];
    char vteseq_n_pool_str102[sizeof("cursor-forward-tabulation")];
    char vteseq_n_pool_str103[sizeof("set-current-file-uri")];
    char vteseq_n_pool_str104[sizeof("linux-console-cursor-attributes")];
    char vteseq_n_pool_str106[sizeof("insert-blank-characters")];
    char vteseq_n_pool_str109[sizeof("change-foreground-colors-st")];
    char vteseq_n_pool_str110[sizeof("change-foreground-colors-bel")];
    char vteseq_n_pool_str111[sizeof("utf-8-character-set")];
    char vteseq_n_pool_str127[sizeof("change-highlight-foreground-colors-st")];
    char vteseq_n_pool_str128[sizeof("change-highlight-foreground-colors-bel")];
  };
static const struct vteseq_n_pool_t vteseq_n_pool_contents =
  {
    "index",
    "next-line",
    "reset-mode",
    "reset-color",
    "decset",
    "save-cursor",
    "soft-reset",
    "change-color-st",
    "change-color-bel",
    "cursor-down",
    "save-mode",
    "tab-set",
    "scroll-down",
    "change-cursor-colors-st",
    "change-cursor-colors-bel",
    "reset-foreground-colors",
    "tab-clear",
    "set-scrolling-region",
    "delete-characters",
    "reset-background-colors",
    "decreset",
    "cursor-position",
    "set-icon-title",
    "cursor-character-absolute",
    "set-scrolling-region-to-end",
    "cursor-backward",
    "window-manipulation",
    "set-icon-and-window-title",
    "set-scrolling-region-from-start",
    "cursor-next-line",
    "set-mode",
    "restore-cursor",
    "reset-highlight-foreground-colors",
    "set-window-title",
    "erase-in-line",
    "screen-alignment-test",
    "reset-highlight-background-colors",
    "cursor-lower-left",
    "insert-lines",
    "return-terminal-id",
    "erase-in-display",
    "cursor-up",
    "erase-characters",
    "delete-lines",
    "scroll-up",
    "full-reset",
    "line-position-absolute",
    "cursor-back-tab",
    "send-secondary-device-attributes",
    "horizontal-and-vertical-position",
    "character-position-absolute",
    "return-terminal-status",
    "cursor-forward",
    "normal-keypad",
    "send-primary-device-attributes",
    "dec-device-status-report",
    "request-terminal-parameters",
    "reset-cursor-colors",
    "restore-mode",
    "reverse-index",
    "set-current-directory-uri",
    "application-keypad",
    "change-background-colors-st",
    "change-background-colors-bel",
    "device-status-report",
    "vertical-tab",
    "form-feed",
    "cursor-preceding-line",
    "character-attributes",
    "iso8859-1-character-set",
    "change-highlight-background-colors-st",
    "change-highlight-background-colors-bel",
    "cursor-forward-tabulation",
    "set-current-file-uri",
    "linux-console-cursor-attributes",
    "insert-blank-characters",
    "change-foreground-colors-st",
    "change-foreground-colors-bel",
    "utf-8-character-set",
    "change-highlight-foreground-colors-st",
    "change-highlight-foreground-colors-bel"
  };
#define vteseq_n_pool ((const char *) &vteseq_n_pool_contents)
#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct vteseq_n_struct *
vteseq_n_lookup (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 81,
      MIN_WORD_LENGTH = 5,
      MAX_WORD_LENGTH = 38,
      MIN_HASH_VALUE = 11,
      MAX_HASH_VALUE = 128
    };

  static const unsigned char lengthtable[] =
    {
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  9,
       0, 10, 11,  6,  0, 11, 10,  0, 15, 16, 11,  9,  7, 11,
       0,  0,  0, 23, 24, 23,  9, 20, 17, 23,  8, 15, 14, 25,
      27, 15, 19, 25, 31, 16,  8, 14, 33, 16, 13, 21, 33, 17,
      12, 18, 16,  9, 16, 12,  9, 10, 22, 15, 32, 32, 27, 22,
      14, 13, 30, 24,  0, 27, 19, 12, 13, 25,  0, 18, 27, 28,
       0,  0, 20, 12,  0,  0,  0,  0,  9,  0, 21, 20,  0,  0,
      23,  0, 37, 38, 25, 20, 31,  0, 23,  0,  0, 27, 28, 19,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0, 37, 38
    };
  static const struct vteseq_n_struct wordlist[] =
    {
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1},
#line 24 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str11, VTE_SEQUENCE_HANDLER(vte_sequence_handler_index)},
      {-1},
#line 32 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str13, VTE_SEQUENCE_HANDLER(vte_sequence_handler_next_line)},
      {-1},
#line 38 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str15, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_mode)},
#line 46 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str16, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_color)},
#line 25 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str17, VTE_SEQUENCE_HANDLER(vte_sequence_handler_decset)},
      {-1},
#line 42 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str19, VTE_SEQUENCE_HANDLER(vte_sequence_handler_sc)},
#line 39 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str20, VTE_SEQUENCE_HANDLER(vte_sequence_handler_soft_reset)},
      {-1},
#line 45 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str22, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_color_st)},
#line 44 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str23, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_color_bel)},
#line 40 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str24, VTE_SEQUENCE_HANDLER(vte_sequence_handler_DO)},
#line 33 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str25, VTE_SEQUENCE_HANDLER(vte_sequence_handler_save_mode)},
#line 27 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str26, VTE_SEQUENCE_HANDLER(vte_sequence_handler_st)},
#line 43 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str27, VTE_SEQUENCE_HANDLER(vte_sequence_handler_scroll_down)},
      {-1}, {-1}, {-1},
#line 83 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str31, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_cursor_color_st)},
#line 82 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str32, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_cursor_color_bel)},
#line 121 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str33, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_foreground_color)},
#line 35 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str34, VTE_SEQUENCE_HANDLER(vte_sequence_handler_tab_clear)},
#line 87 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str35, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_scrolling_region)},
#line 75 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str36, VTE_SEQUENCE_HANDLER(vte_sequence_handler_DC)},
#line 118 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str37, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_background_color)},
#line 28 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str38, VTE_SEQUENCE_HANDLER(vte_sequence_handler_decreset)},
#line 66 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str39, VTE_SEQUENCE_HANDLER(vte_sequence_handler_cursor_position)},
#line 63 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str40, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_icon_title)},
#line 125 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str41, VTE_SEQUENCE_HANDLER(vte_sequence_handler_cursor_character_absolute)},
#line 89 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str42, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_scrolling_region_to_end)},
#line 65 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str43, VTE_SEQUENCE_HANDLER(vte_sequence_handler_LE)},
#line 81 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str44, VTE_SEQUENCE_HANDLER(vte_sequence_handler_window_manipulation)},
#line 128 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str45, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_icon_and_window_title)},
#line 88 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str46, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_scrolling_region_from_start)},
#line 70 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str47, VTE_SEQUENCE_HANDLER(vte_sequence_handler_cursor_next_line)},
#line 29 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str48, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_mode)},
#line 62 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str49, VTE_SEQUENCE_HANDLER(vte_sequence_handler_rc)},
#line 106 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str50, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_highlight_foreground_color)},
#line 73 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str51, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_window_title)},
#line 53 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str52, VTE_SEQUENCE_HANDLER(vte_sequence_handler_erase_in_line)},
#line 94 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str53, VTE_SEQUENCE_HANDLER(vte_sequence_handler_screen_alignment_test)},
#line 103 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str54, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_highlight_background_color)},
#line 74 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str55, VTE_SEQUENCE_HANDLER(vte_sequence_handler_cursor_lower_left)},
#line 49 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str56, VTE_SEQUENCE_HANDLER(vte_sequence_handler_insert_lines)},
#line 78 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str57, VTE_SEQUENCE_HANDLER(vte_sequence_handler_return_terminal_id)},
#line 72 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str58, VTE_SEQUENCE_HANDLER(vte_sequence_handler_erase_in_display)},
#line 30 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str59, VTE_SEQUENCE_HANDLER(vte_sequence_handler_UP)},
#line 71 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str60, VTE_SEQUENCE_HANDLER(vte_sequence_handler_erase_characters)},
#line 47 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str61, VTE_SEQUENCE_HANDLER(vte_sequence_handler_delete_lines)},
#line 34 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str62, VTE_SEQUENCE_HANDLER(vte_sequence_handler_scroll_up)},
#line 36 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str63, VTE_SEQUENCE_HANDLER(vte_sequence_handler_full_reset)},
#line 99 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str64, VTE_SEQUENCE_HANDLER(vte_sequence_handler_line_position_absolute)},
#line 64 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str65, VTE_SEQUENCE_HANDLER(vte_sequence_handler_bt)},
#line 149 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str66, VTE_SEQUENCE_HANDLER(vte_sequence_handler_send_secondary_device_attributes)},
#line 148 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str67, VTE_SEQUENCE_HANDLER(vte_sequence_handler_horizontal_and_vertical_position)},
#line 130 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str68, VTE_SEQUENCE_HANDLER(vte_sequence_handler_character_position_absolute)},
#line 100 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str69, VTE_SEQUENCE_HANDLER(vte_sequence_handler_return_terminal_status)},
#line 60 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str70, VTE_SEQUENCE_HANDLER(vte_sequence_handler_RI)},
#line 55 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str71, VTE_SEQUENCE_HANDLER(vte_sequence_handler_normal_keypad)},
#line 146 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str72, VTE_SEQUENCE_HANDLER(vte_sequence_handler_send_primary_device_attributes)},
#line 122 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str73, VTE_SEQUENCE_HANDLER(vte_sequence_handler_dec_device_status_report)},
      {-1},
#line 131 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str75, VTE_SEQUENCE_HANDLER(vte_sequence_handler_request_terminal_parameters)},
#line 84 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str76, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reset_cursor_color)},
#line 50 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str77, VTE_SEQUENCE_HANDLER(vte_sequence_handler_restore_mode)},
#line 56 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str78, VTE_SEQUENCE_HANDLER(vte_sequence_handler_reverse_index)},
#line 156 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str79, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_current_directory_uri)},
      {-1},
#line 76 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str81, VTE_SEQUENCE_HANDLER(vte_sequence_handler_application_keypad)},
#line 117 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str82, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_background_color_st)},
#line 116 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str83, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_background_color_bel)},
      {-1}, {-1},
#line 86 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str86, VTE_SEQUENCE_HANDLER(vte_sequence_handler_device_status_report)},
#line 52 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str87, VTE_SEQUENCE_HANDLER(vte_sequence_handler_vertical_tab)},
      {-1}, {-1}, {-1}, {-1},
#line 31 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str92, VTE_SEQUENCE_HANDLER(vte_sequence_handler_form_feed)},
      {-1},
#line 92 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str94, VTE_SEQUENCE_HANDLER(vte_sequence_handler_cursor_preceding_line)},
#line 85 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str95, VTE_SEQUENCE_HANDLER(vte_sequence_handler_character_attributes)},
      {-1}, {-1},
#line 111 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str98, VTE_SEQUENCE_HANDLER(vte_sequence_handler_local_charset)},
      {-1},
#line 102 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str100, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_highlight_background_color_st)},
#line 101 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str101, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_highlight_background_color_bel)},
#line 126 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str102, VTE_SEQUENCE_HANDLER(vte_sequence_handler_ta)},
#line 157 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str103, VTE_SEQUENCE_HANDLER(vte_sequence_handler_set_current_file_uri)},
#line 147 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str104, VTE_SEQUENCE_HANDLER(vte_sequence_handler_noop)},
      {-1},
#line 108 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str106, VTE_SEQUENCE_HANDLER(vte_sequence_handler_insert_blank_characters)},
      {-1}, {-1},
#line 120 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str109, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_foreground_color_st)},
#line 119 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str110, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_foreground_color_bel)},
#line 80 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str111, VTE_SEQUENCE_HANDLER(vte_sequence_handler_utf_8_charset)},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 105 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str127, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_highlight_foreground_color_st)},
#line 104 "vteseq-n.gperf"
      {(int)(long)&((struct vteseq_n_pool_t *)0)->vteseq_n_pool_str128, VTE_SEQUENCE_HANDLER(vte_sequence_handler_change_highlight_foreground_color_bel)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = vteseq_n_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        if (len == lengthtable[key])
          {
            register const char *s = wordlist[key].seq + vteseq_n_pool;

            if (*str == *s && !memcmp (str + 1, s + 1, len - 1))
              return &wordlist[key];
          }
    }
  return 0;
}
