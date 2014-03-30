/* This file is part of the 'stringi' package for R.
 * Copyright (c) 2013-2014, Marek Gagolewski and Bartek Tartanus
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "stri_stringi.h"
#include <cstring>
#include <cstdlib>


#define STRI__MAKE_CALL_METHOD(name, args) \
   {#name, (DL_FUNC)&name, args}

/**
 * List of functions available in R via .Call()
 *
 * Form:
 * \code{\{"method_name", (DL_FUNC)pointer, number_of_args\}} -
 * this is generated by the STRI__MAKE_CALL_METHOD macro.
 */
static const R_CallMethodDef cCallMethods[] = {

   STRI__MAKE_CALL_METHOD(stri_trans_case,                 3),
//   STRI__MAKE_CALL_METHOD(stri_charcategories,             0),  // TO BE v>=0.2
//   STRI__MAKE_CALL_METHOD(stri_chartype,                   1),  // TO BE v>=0.2
   STRI__MAKE_CALL_METHOD(stri_cmp,                        3),
   STRI__MAKE_CALL_METHOD(stri_cmp_logical,                4),
   STRI__MAKE_CALL_METHOD(stri_count_charclass,            2),
   STRI__MAKE_CALL_METHOD(stri_count_fixed,                3),
   STRI__MAKE_CALL_METHOD(stri_count_regex,                3),
   STRI__MAKE_CALL_METHOD(stri_detect_charclass,           2),
   STRI__MAKE_CALL_METHOD(stri_detect_fixed,               3),
   STRI__MAKE_CALL_METHOD(stri_detect_regex,               3),
   STRI__MAKE_CALL_METHOD(stri_dup,                        2),
   STRI__MAKE_CALL_METHOD(stri_enc_detect,                 2),
   STRI__MAKE_CALL_METHOD(stri_enc_detect2,                2),
   STRI__MAKE_CALL_METHOD(stri_enc_isenc,                  2),
   STRI__MAKE_CALL_METHOD(stri_enc_info,                   1),
   STRI__MAKE_CALL_METHOD(stri_enc_isnf,                   2),
   STRI__MAKE_CALL_METHOD(stri_enc_list,                   0),
   STRI__MAKE_CALL_METHOD(stri_enc_mark,                   1),
   STRI__MAKE_CALL_METHOD(stri_enc_nf,                     2),
   STRI__MAKE_CALL_METHOD(stri_enc_set,                    1),
   STRI__MAKE_CALL_METHOD(stri_enc_fromutf32,              1),
   STRI__MAKE_CALL_METHOD(stri_enc_toascii,                1),
   STRI__MAKE_CALL_METHOD(stri_enc_toutf8,                 3),
   STRI__MAKE_CALL_METHOD(stri_enc_toutf32,                1),
   STRI__MAKE_CALL_METHOD(stri_encode,                     4),
   STRI__MAKE_CALL_METHOD(stri_encode_from_marked,         3),
   STRI__MAKE_CALL_METHOD(stri_escape_unicode,             1),
   STRI__MAKE_CALL_METHOD(stri_extract_first_charclass,    2),
   STRI__MAKE_CALL_METHOD(stri_extract_last_charclass,     2),
   STRI__MAKE_CALL_METHOD(stri_extract_all_charclass,      3),
   STRI__MAKE_CALL_METHOD(stri_extract_first_fixed,        3),
   STRI__MAKE_CALL_METHOD(stri_extract_last_fixed,         3),
   STRI__MAKE_CALL_METHOD(stri_extract_all_fixed,          3),
   STRI__MAKE_CALL_METHOD(stri_extract_first_regex,        3),
   STRI__MAKE_CALL_METHOD(stri_extract_last_regex,         3),
   STRI__MAKE_CALL_METHOD(stri_extract_all_regex,          3),
   STRI__MAKE_CALL_METHOD(stri_flatten_withressep,         2),
   STRI__MAKE_CALL_METHOD(stri_info,                       0),
   STRI__MAKE_CALL_METHOD(stri_isempty,                    1),
   STRI__MAKE_CALL_METHOD(stri_join_withcollapse,          3),
   STRI__MAKE_CALL_METHOD(stri_join2_nocollapse,           2),
//   STRI__MAKE_CALL_METHOD(stri_justify,                    2),  // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_length,                     1),
   STRI__MAKE_CALL_METHOD(stri_locale_info,                1),
   STRI__MAKE_CALL_METHOD(stri_locale_list,                0),
   STRI__MAKE_CALL_METHOD(stri_locale_set,                 1),
   STRI__MAKE_CALL_METHOD(stri_locate_first_charclass,     2),
   STRI__MAKE_CALL_METHOD(stri_locate_last_charclass,      2),
   STRI__MAKE_CALL_METHOD(stri_locate_all_charclass,       3),
   STRI__MAKE_CALL_METHOD(stri_locate_last_fixed,          3),
   STRI__MAKE_CALL_METHOD(stri_locate_first_fixed,         3),
   STRI__MAKE_CALL_METHOD(stri_locate_all_fixed,           3),
   STRI__MAKE_CALL_METHOD(stri_locate_all_regex,           3),
   STRI__MAKE_CALL_METHOD(stri_locate_first_regex,         3),
   STRI__MAKE_CALL_METHOD(stri_locate_last_regex,          3),
   STRI__MAKE_CALL_METHOD(stri_match_first_regex,          3),
   STRI__MAKE_CALL_METHOD(stri_match_last_regex,           3),
   STRI__MAKE_CALL_METHOD(stri_match_all_regex,            3),
   STRI__MAKE_CALL_METHOD(stri_numbytes,                   1),
   STRI__MAKE_CALL_METHOD(stri_order_or_sort,              5),
//   STRI__MAKE_CALL_METHOD(stri_pad,                        3), // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_string,         2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_double,         2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_integer,        2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_logical,        2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_raw,            2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_string_1,       2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_double_1,       2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_integer_1,      2),
   STRI__MAKE_CALL_METHOD(stri_prepare_arg_logical_1,      2),
   STRI__MAKE_CALL_METHOD(stri_replace_all_fixed,          4),
   STRI__MAKE_CALL_METHOD(stri_replace_first_fixed,        4),
   STRI__MAKE_CALL_METHOD(stri_replace_last_fixed,         4),
   STRI__MAKE_CALL_METHOD(stri_replace_all_regex,          4),
   STRI__MAKE_CALL_METHOD(stri_replace_first_regex,        4),
   STRI__MAKE_CALL_METHOD(stri_replace_last_regex,         4),
   STRI__MAKE_CALL_METHOD(stri_replace_all_charclass,      3),
   STRI__MAKE_CALL_METHOD(stri_replace_first_charclass,    3),
   STRI__MAKE_CALL_METHOD(stri_replace_last_charclass,     3),
   STRI__MAKE_CALL_METHOD(stri_reverse,                    1),
   STRI__MAKE_CALL_METHOD(stri_split_charclass,            4),
   STRI__MAKE_CALL_METHOD(stri_split_fixed,                5),
   STRI__MAKE_CALL_METHOD(stri_split_lines,                3),
   STRI__MAKE_CALL_METHOD(stri_split_lines1,               1),
   STRI__MAKE_CALL_METHOD(stri_split_regex,                5),
//   STRI__MAKE_CALL_METHOD(stri_split_pos,              3), // TODO: version >= 0.2
   STRI__MAKE_CALL_METHOD(stri_stats_general,              1),
   STRI__MAKE_CALL_METHOD(stri_stats_latex,                1),
   STRI__MAKE_CALL_METHOD(stri_sub,                        4),
   STRI__MAKE_CALL_METHOD(stri_sub_replacement,            5),
   STRI__MAKE_CALL_METHOD(stri_subst_na,			           2),
   STRI__MAKE_CALL_METHOD(stri_test_Rmark,                 1),
   STRI__MAKE_CALL_METHOD(stri_test_returnasis,            1),
   STRI__MAKE_CALL_METHOD(stri_test_UnicodeContainer16,    1),
   STRI__MAKE_CALL_METHOD(stri_test_UnicodeContainer8,     1),
   STRI__MAKE_CALL_METHOD(stri_trim_both,                  2),
   STRI__MAKE_CALL_METHOD(stri_trim_left,                  2),
   STRI__MAKE_CALL_METHOD(stri_trim_right,                 2),
   STRI__MAKE_CALL_METHOD(stri_unescape_unicode,           1),
//   STRI__MAKE_CALL_METHOD(stri_trim_double,                3), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_width,                      1), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap,                       4), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap_greedy,                3), // TODO: version >= 0.2
//   STRI__MAKE_CALL_METHOD(stri_wrap_dynamic,               3), // TODO: version >= 0.2

   // the list must be NULL-terminated:
   {NULL,                           NULL,                  0}

};


void stri_set_icu_data_directory(const char* libpath)
{
   // libpath == "...../libs"      -> "...../libs"
   // libpath == "...../libs/i386" -> "...../libs"
   // libpath == "...../libs/x64"  -> "...../libs"

   string dir(libpath);
   size_t idx = dir.rfind("libs");
   if (idx == string::npos) return; // this shouldn't happen

   dir = dir.substr(0, idx+5); // 5 == strlen("libs/") or strlen("libs\\")
   u_setDataDirectory(dir.c_str());

   // anyway, if .dat file will not be found,
   // ICU will use system data (may be stub)
}


/**
 * Library initialization.
 *
 * R calls this automatically on lib load/attach.
 */
extern "C" void R_init_stringi(DllInfo *dll)
{
   R_registerRoutines(dll, NULL, cCallMethods, NULL, NULL);
   R_useDynamicSymbols(dll, Rboolean(FALSE));

   if (!SUPPORT_UTF8) {
      /* Rconfig.h states that all R platforms supports that */
      Rf_error("R does not support UTF-8 encoding.");
   }

   stri_set_icu_data_directory((char*)*(char**)(dll) /* dll->path */);


#ifndef NDEBUG
   fprintf(stdout, "!NDEBUG: ************************************************\n");
   fprintf(stdout, "!NDEBUG: Dynamic library `stringi` loaded\n");
   fprintf(stdout, "!NDEBUG: Check out http://stringi.rexamine.com\n");
   fprintf(stdout, "!NDEBUG: \n");
   fprintf(stdout, "!NDEBUG: Please send bug reports to stringi@rexamine.com \n");
   fprintf(stdout, "!NDEBUG: or at https://github.com/Rexamine/stringi/issues\n");
   fprintf(stdout, "!NDEBUG: \n");
   fprintf(stdout, "!NDEBUG: Have fun testing! :-)\n");
   fprintf(stdout, "!NDEBUG: ************************************************\n");

//    UErrorCode status;
//    u_init(&status);
//    if (U_FAILURE(status))
//      error("ICU init failed: %s", u_errorName(status));
#endif
}




///**
// * ... not needed ...
// */
//extern "C" void  R_unload_stringi(DllInfo *info)
//{
//#ifndef NDEBUG
//   fprintf(stdout, "!NDEBUG: Dynamic library 'stringi' unloaded.\n");
////   u_cleanup(); // this is just for DEBUG- memtrace
//#endif
//}
