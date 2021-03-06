require("testthat")
context("test-detect-regex.R")

test_that("stri_detect_regex", {
   expect_identical(stri_detect_regex(NA, NA), NA)
   expect_identical(stri_detect_regex(character(0), character(0)), logical(0))

   suppressWarnings(expect_identical(stri_detect_regex("",""), NA))
   suppressWarnings(expect_identical(stri_detect_regex("a",""), NA))
   suppressWarnings(expect_identical(stri_detect_regex("","a"), FALSE))
   expect_identical(stri_detect_regex(c("","ala"),"ala"), c(FALSE, TRUE))
   expect_identical(stri_detect_regex(c("","ala", "ala", "bbb"),c("ala", "bbb")), c(FALSE, FALSE, TRUE, TRUE))
   expect_identical(stri_detect_regex(c("ala","", "", "bbb"),c("ala", "bbb")), c(TRUE, FALSE, FALSE, TRUE))

   expect_identical(stri_detect_regex('a', c('a', 'b', 'c')), c(T,F,F))
   expect_identical(stri_detect_regex(c('a', 'b', 'c'), 'a'), c(T,F,F))
   suppressWarnings(expect_identical(stri_detect_regex(LETTERS[1:2], LETTERS[1:3]), c(T,T,F)))
   suppressWarnings(expect_identical(stri_detect_regex(LETTERS[1:3], LETTERS[1:5]), c(T,T,T,F,F)))
   suppressWarnings(expect_identical(stri_detect_regex(LETTERS[1:2], LETTERS[1:5]), c(T,T,F,F,F)))
   suppressWarnings(expect_identical(stri_detect_regex(LETTERS[1:4], LETTERS[1:5]), c(T,T,T,T,F)))

   expect_identical(stri_detect_regex(c("\u0105\u0106\u0107", "\u0105\u0107"), "\u0106*"), c(TRUE, TRUE)) # match of zero length
   expect_identical(stri_detect_regex(c("\u0105\u0106\u0107", "\u0105\u0107"), "(?<=\u0106)"), c(TRUE, FALSE)) # match of zero length:


   s <- c("Lorem", "123", " ", " ", "kota", "4\t\u0105")
   p <- c("[[:alpha:]]+", "[[:blank:]]+")
   expect_identical(stri_detect_regex(s, p), c(T, F, F, T, T, T))
   expect_identical(stri_detect_regex("Lo123\trem", c("[[:alpha:]]", "[4-9]+")), c(T, F))

   expect_warning(stri_detect_regex(rep("asd", 5), rep("[A-z]", 2)))
   expect_error(stri_detect_regex("Ala", "{}"))

   expect_identical(stri_detect_regex("aaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaa"), TRUE)
   expect_identical(stri_detect_regex("aaaaaaaaaaaaaaa",  "aaaaaaaaaaaaaaa"), TRUE)
   expect_identical(stri_detect_regex("aaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaa"), TRUE)

   expect_equivalent(stri_detect_regex("\u0105\u0105\u0105\u0105\u0105\u0105\u0105b","\u0105+b$"),TRUE)

   expect_equivalent(stri_detect_regex("aaaab", "ab"), TRUE)
   expect_equivalent(stri_detect_regex("bababababaab", "aab"), TRUE)

   expect_equivalent(stri_detect_regex("caabaab", "(a+b)+"), TRUE)
   expect_equivalent(stri_detect_regex("caacbaab", "(a+b)+"), TRUE)
   expect_equivalent(stri_detect_regex("caacbacab", "(a+b)+"), TRUE)
   expect_equivalent(stri_detect_regex("caacbacacb", "(a+b)+"), FALSE)

   # ICU-bugs (#147)
   expect_identical(stri_detect_regex("***aafoo*** - ICU BUG TEST", "(?<=aa)foo"), TRUE)
   expect_identical(stri_detect_regex("***a\u0105foo*** - ICU BUG TEST", "(?<=a\u0105)foo"), TRUE)
   expect_identical(stri_detect_regex("***a\U00020000foo*** - ICU BUG TEST", "(?<=a\U00020000)foo"), TRUE)
})
