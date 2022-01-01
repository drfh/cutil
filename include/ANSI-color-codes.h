/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

//	Formatting
#define	kPLAIN			"0"
#define	kBOLD			"1"
#define	kUNDERLINE		"4"

#define	KSTRINFIFY(tok)		#tok

//	ANSI macros
#define	kANSI3(a,b,c)		"\x1B["#a";"#b";"#c""
#define	kANSI2(a,b)			"\x1B["a";"#b"m"
#define	kANSI(x)			kANSI2(kPLAIN,x)


// Regular text
// #define BLK "\x1B[0;30m"
#define BLK kANSI(30)
#define RED kANSI(31)
#define GRN kANSI(32)
#define YEL kANSI(33)
#define BLU kANSI(34)
#define MAG kANSI(35)
#define CYN kANSI(36)
#define WHT kANSI(37)

// Regular bold text
#define BBLK kANSI2(kBOLD,30)
#define BRED kANSI2(kBOLD,31)
#define BGRN kANSI2(kBOLD,32)
#define BYEL kANSI2(kBOLD,33)
#define BBLU kANSI2(kBOLD,34)
#define BMAG kANSI2(kBOLD,35)
#define BCYN kANSI2(kBOLD,36)
#define BWHT kANSI2(kBOLD,37)

// Regular underline text
#define UBLK kANSI2(kUNDERLINE,30)
#define URED kANSI2(kUNDERLINE,31)
#define UGRN kANSI2(kUNDERLINE,32)
#define UYEL kANSI2(kUNDERLINE,33)
#define UBLU kANSI2(kUNDERLINE,34)
#define UMAG kANSI2(kUNDERLINE,35)
#define UCYN kANSI2(kUNDERLINE,36)
#define UWHT kANSI2(kUNDERLINE,37)

//Regular background
#define BLKB "\x1B[40m"
#define REDB "\x1B[41m"
#define GRNB "\x1B[42m"
#define YELB "\x1B[43m"
#define BLUB "\x1B[44m"
#define MAGB "\x1B[45m"
#define CYNB "\x1B[46m"
#define WHTB "\x1B[47m"

//High intensty background
#define BLKHB "\x1B[0;100m"
#define REDHB "\x1B[0;101m"
#define GRNHB "\x1B[0;102m"
#define YELHB "\x1B[0;103m"
#define BLUHB "\x1B[0;104m"
#define MAGHB "\x1B[0;105m"
#define CYNHB "\x1B[0;106m"
#define WHTHB "\x1B[0;107m"

//High intensty text
#define HBLK "\x1B[0;90m"
#define HRED "\x1B[0;91m"
#define HGRN "\x1B[0;92m"
#define HYEL "\x1B[0;93m"
#define HBLU "\x1B[0;94m"
#define HMAG "\x1B[0;95m"
#define HCYN "\x1B[0;96m"
#define HWHT "\x1B[0;97m"

//Bold high intensity text
#define BHBLK "\x1B[1;90m"
#define BHRED "\x1B[1;91m"
#define BHGRN "\x1B[1;92m"
#define BHYEL "\x1B[1;93m"
#define BHBLU "\x1B[1;94m"
#define BHMAG "\x1B[1;95m"
#define BHCYN "\x1B[1;96m"
#define BHWHT "\x1B[1;97m"

//Reset
#define TERM_RESET "\x1B[0m"
