; // MyEventProvider.mc 

; // This is the header section.


SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
              )


FacilityNames=(System=0x0:FACILITY_SYSTEM
               Runtime=0x2:FACILITY_RUNTIME
               Stubs=0x3:FACILITY_STUBS
               Io=0x4:FACILITY_IO_ERROR_CODE
              )

LanguageNames=(English=0x409:MSG00409
			   German=0x0407:MSG00407
			  )


; // The following are the categories of events.

MessageIdTypedef=WORD

MessageId=0x1
SymbolicName=NETWORK_CATEGORY
Language=English
Network Events
.

Language=German
Netzwerk Ereignisse
.

MessageId=0x2
SymbolicName=DATABASE_CATEGORY
Language=English
Database Events
.

Language=German
Datenbank Ereignisse
.

MessageId=0x3
SymbolicName=UI_CATEGORY
Language=English
UI Events
.

Language=German
Ereignisse Benutzerschnittstelle
.


; // The following are the message definitions.

MessageIdTypedef=DWORD

MessageId=0x100
Severity=Error
Facility=Runtime
SymbolicName=MSG_ERROR_TEXT
Language=English
%1.
.

Language=German
%1.
.

MessageId=0x101
Severity=Error
Facility=System
SymbolicName=MSG_BAD_FILE_CONTENTS
Language=English
File '%1' contains content that is not valid.
.

Language=German
Datei '%1' enthält ungültigen Inhalt.
.

MessageId=0x102
Severity=Warning
Facility=System
SymbolicName=MSG_RETRIES
Language=English
There have been %1 retries with %2 success! Disconnect from the server and try again later.
.

Language=German
Es gab %1 Versuch(e) mit %2 Erfolg! Trennen Sie die Verbindung zum Server und versuchen Sie es später noch einmal.
.

MessageId=0x103
Severity=Informational
Facility=System
SymbolicName=MSG_COMPUTE_CONVERSION
Language=English
%1 %%4096 = %2 %%4097. 
.

Language=German
%1 %%4096 = %2 %%4097. 
.


; // The following are the parameter strings */


MessageId=0x1000
Severity=Success
Facility=System
SymbolicName=QUARTS_UNITS
Language=English
quarts%0
.

Language=German
Quarts%0
.

MessageId=0x1001
Severity=Success
Facility=System
SymbolicName=GALLONS_UNITS
Language=English
gallons%0
.

Language=German
Gallonen%0
.


