# CIS_200_Assignment3

## Team
Gustavo Nascimento Santos de Abreu
Dheya Alrabeei

## Division
Gustavo worked on functions, such as, `int main()`, `void SpamAnalyzer::readMessageFile()`, `void SpamAnalyzer::runFullSpamAnalysis()`, `void SpamAnalyzer::processQueue()`, and on some class definitions.

Dheya worked on drawing the diagram, on other functions and some class definitions. 

### Command used to compile project

```bash
g++ '.\Source Files\Utility.cpp' '.\Source Files\TestMessage.cpp' '.\Source Files\SpamAnalyzer.cpp' '.\Source Files\SpamLoadAndProcess.cpp' '.\Source Files\Message.cpp' '.\Source Files\InstantMessage.cpp' '.\Source Files\Email.cpp' '.\Source Files\Assign3.cpp' -o Assign3
```

### Command used to run project in powershell with a test script file
```bash
Get-Content ".\Resource Files\test_script.txt" | .\Assign3.exe
```

### Command used to run project in command prompt and mac terminal with a test script file
```bash
.\Assign3.exe < "Resource FIles\test_script.txt"
```

### Example resource files

**<u>NOTE:</u> They must be included under a "root/Resource Files/" folder, and they must have same name and format as shown below**

#### message.txt
```txt
Email, alice@example.com, 2025-09-24 10:30, "Password reset required",
cc=bob@example.com
Text, +1555123456, 2025-09-24 11:02, "Urgent: send bank details"
Instant, charlie, 2025-09-24 11:15, "Lunch today?", platform=Discord
Email, spammer@phish.com, 2025-09-24 11:20, "Click here to win a free gift!"
GARBLED MESSAGE 1: missing timestamp and content

```

#### valid_senders.txt

```txt
alice@example.com
+1555123456
charlie

```

#### watch_keyword.txt

```txt
urgent
password
bank
click
free
gift
account

```