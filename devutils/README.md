## JailBreak

On the new Topfield SRP-2100 series HDTV set top boxes, Topfield has
made the brilliant decision to implement the famous TAP API, which has
been a big success on the TF5000 and TF6000 models. Opposed to the older
STBs, the SRP-2100 is based on Linux. Due to whatever reason, the main
application does not allow TAPs to call Linux system commands, they are
restricted to the TAP-API. While this might be o.k. for most TAPs, there
are still a lot of things which cannot be done because of the limited
functionality of the API.

JailBreak modifies the compiled TAP so that it passes the check upon
launch regardless of what you have coded.

Usage: JailBreak <filename.tap>

Or to automake the procedure of modifying the TAP, some entries in the
tool chain are needed. The following instruction is based on the
"Installationsanleitung fur die TAP-Entwicklungsumgebungen" TV-Junkie
and FireBird.

1. Copy "JailBreak.exe" into "C:\Work\cygwin\opt\crosstool\bin"
2. Open "C:\Work\API\TMS\include\tool.mk" with an Unix-aware editor
3. Add the JB line after AWK

    AWK 	= awk
    JB 	= JailBreak.exe

4. Save and exit the editor
5. Open the Makefile of your project and add the last line of the following block:

    $(TAP_APP): ${TAP_OBJS}
	    @echo "[Linking... $@]"
	    $(Q_)$(LD) -shared --no-undefined --allow-shlib-undefined  -o $@ ${TAP_OBJS} $(TAP_LIBS) -Map ${TAP_MAP}
	    $(Q_)$(JB) $(TAP_APP)

6. Save and exit

Warning: due to a limited number of machines on the market and because
this hack is brand new, there has been nearly no testing of the effects
of this JailBreak hack nor the possibilities opened by the hack. The
most worrying thing is that SRP seem to have no loader. If this proves
to be true, there would not be any emergency procedure to reflash a
damaged firmware.
