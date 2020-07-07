# Bangla_Markup_Creator
Write a simple text document in Bangla and convert it to a tex, html or pdf file.

## Input file format
Input file should be a `.txt` file.

The file has two sections.
- Heading
- Body

Heading and body are seperated by a single `%` in a line.

### Heading
You can specify Title, Author and Date of your writing here.
- Title precedes with `$`
- Author precedes with `@`
- Date precedes with `>`

### Body
Your main content goes here. Sections, paragraphs and numbered lists are currently supported.

**Section:** To specify section title, precede section title with a `#`

**Paragraph:** To generate a new paragraph, insert a line gap after the current paragraph.

**Numbered Lists:** Only Bangla numbers are currently supported. If a line is preceded with a bangla number and `)`, `.` or `।` character, that line is considered to be a list item. ***However, you must start your list number from `১`(1 in Bangla).*** A line with no preceding number will complete the list.

Example:
```
$শিরোনাম
@আসিফ ইমতিয়াল
>৭ জুলাই, ২০২০
%
দুঃখজনক হলেও সত্য যে, ইংরেজিতে লাতিন Lorem Ipsum সূচক নমুনা লেখা (dummy texts) থাকলেও বাংলা ভাষায় এরকম কোনো লেখা নেই। তাই নিজের তাগিদেই বাংলা ভাষার জন্য প্রথম নমুনা লেখা তৈরি করলাম, এ হলো বাংলা Lorem ipsum – কিন্তু তার অনুবাদ নয়। আমি একে নামকরণ করেছি: অর্থহীন লেখা!
এখানে কিছু অর্থহীন কথার তালিকা দিচ্ছি।
১) অর্থ থাকলেই যে কোন কথার অন্তরে অর্থ থাকবে তা নয়।
২) প্রাতিষ্ঠানিকভাবে আমার মনে হয় প্রতিটি প্রতিষ্ঠানের কিছু ব্যক্তিগত স্বাধীনতা আছে।
#অর্থহীন লেখা
অর্থহীন লেখা যার মাঝে আছে অনেক কিছু। হ্যাঁ, এই লেখার মাঝেই আছে অনেক কিছু। যদি তুমি মনে করো, এটা তোমার কাজে লাগবে, তাহলে তা লাগবে কাজে। নিজের ভাষায় লেখা দেখতে অভ্যস্ত হও। মনে রাখবে লেখা অর্থহীন হয়, যখন তুমি তাকে অর্থহীন মনে করো; আর লেখা অর্থবোধকতা তৈরি করে, যখন তুমি তাতে অর্থ ঢালো। যেকোনো লেখাই তোমার কাছে অর্থবোধকতা তৈরি করতে পারে, যদি তুমি সেখানে অর্থদ্যোতনা দেখতে পাও। …ছিদ্রান্বেষণ? না, তা হবে কেন?

যে কথাকে কাজে লাগাতে চাও, তাকে কাজে লাগানোর কথা চিন্তা করার আগে ভাবো, তুমি কি সেই কথার জাদুতে আচ্ছন্ন হয়ে গেছ কিনা। তুমি যদি নিশ্চিত হও যে, তুমি কোনো মোহাচ্ছাদিত আবহে আবিষ্ট হয়ে অন্যের শেখানো বুলি আত্মস্থ করছো না, তাহলে তুমি নির্ভয়ে, নিশ্চিন্তে অগ্রসর হও। তুমি সেই কথাকে জানো, বুঝো, আত্মস্থ করো; মনে রাখবে, যা অনুসরণ করতে চলেছো, তা আগে অনুধাবন করা জরুরি; এখানে কিংকর্তব্যবিমূঢ় হবার কোনো সুযোগ নেই।
```
## Help
**SYNOPSIS**

`./muc [OPTIONS] [FILES]`

**OPTIONS**
- `-v` shows version
- `-pdf` compile pdf files. You must have xelatex compiler installed in your system to compile pdf. Also you must have kalpurush.ttf and Siyam-Rupali.ttf fonts installed in your system.

## Installation
```
git clone https://github.com/Imtial/Bangla_Markup_Creator.git
make
```
