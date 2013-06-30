FontManager V2 creates the new Unicode capable ufnt font files. Because of the size of these files,
FBLib doesn’t support the creation of source files of ufnt files. Normally, the FontManager will
only copy those glyphs, which are included in the selected font. If the “Full charset” checkmark
is checked, Windows will substitute the missing glyphs with ones from other fonts. This will generate
a complete ufnt although the substituted glyphs will look differently (see the Korean text in the
demo TAP). Be aware that the generation of a complete ufnt will take a considerable amount of time.


Even if the ufnt file may be quite large, the FontManager inside a TAP will just load the used
characters and therefore might use less space than the FontManager V1.
