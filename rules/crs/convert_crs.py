#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import re
import sys
import git     ## pip install gitpython
import xlwt    ## pip install xlwt
import getopt

### CRR Project
CRS_GIT = "https://github.com/coreruleset/coreruleset.git"

CRS_PATH=""
OUT_PATH=""

FILE_LIST = {
    "SQLi"   : "REQUEST-942-APPLICATION-ATTACK-SQLI.conf",
    "XSS"    : "REQUEST-941-APPLICATION-ATTACK-XSS.conf",
    "LFI"    : "REQUEST-930-APPLICATION-ATTACK-LFI.conf",
    "RFI"    : "REQUEST-931-APPLICATION-ATTACK-RFI.conf",
    "RCE"    : "REQUEST-932-APPLICATION-ATTACK-RCE.conf",
    "PHP"    : "REQUEST-933-APPLICATION-ATTACK-PHP.conf",
    "JAVA"   : "REQUEST-944-APPLICATION-ATTACK-JAVA.conf",
    "NODEJS" : "REQUEST-934-APPLICATION-ATTACK-NODEJS.conf",
}

#
# rule_id, phase, severity, match_field, signature, msg, 
# 
def parse_rules(worksheet, item):
    filename = OUT_PATH + item + ".conf"
    Row = 0
    with open(filename, encoding="utf-8", mode="r") as in_f:
        for line in in_f:
            Row = Row + 1
            print("===[%s]->line[%d]" % (item, Row))
            result = re.search(r'^SecRule\s+([^\s]+)\s+(".+?")\s+(".+")', line)
            # sub-rule
            if result is None:
                result = re.search(r'^\s+SecRule\s+([^\s]+)\s"(.+?)"\s+', line)
                if result is None:
                    print("=== ERROR: Invalid line !")
                    return
                else:
                    print("==== SUB-RULE")
                    worksheet.write(Row, 4, result[1])  # sub-match
                    worksheet.write(Row, 5, result[2])  # sub-rule
            else:
                result_sub = re.search(r""""id:(\d+),\s+phase:(\d+),.+?msg:'(.+?)'.+?severity:'(.+?)'""", result[3])
                if result_sub is None:
                    print("==== ERROR: result_sub is None !")
                    sys.exit(4)
                    return       
                worksheet.write(Row, 1, result_sub[1]) # rule_id
                worksheet.write(Row, 2, result_sub[2]) # phase
                worksheet.write(Row, 3, result_sub[4]) # severity
                worksheet.write(Row, 4, result[1])  # match_field
                worksheet.write(Row, 5, result[2]) # rule
                worksheet.write(Row, 6, result_sub[3]) # msg


def compress_rules(item):
    if sys.platform == "win32":
        path = CRS_PATH + "\\rules\\" + FILE_LIST[item]
    else:
        path = CRS_PATH + "/rules/" + FILE_LIST[item]

    if not os.path.exists(path):
        print("=== ERROR: File %s not exist !\n" % path)
        return

    # open modsecurity file
    with open(path, encoding="utf-8", mode="r") as in_f:
        content = in_f.read()
        # delete comment line
        content = re.sub(r"^#.*$", "", content, flags=re.M)
        # delete wrapper line
        content = re.sub(r"\\\s*$\n", "", content, flags=re.M)
        # delete marker line
        content = re.sub(r"^SecMarker.+?$", "", content, flags=re.M)
        # delete PARANOIA line
        content = re.sub(r"^SecRule TX.+?$", "", content, flags=re.M)
        # delete empty line
        content = re.sub(r"^$\n*", "", content, flags=re.M)

        # output result
        outpath = OUT_PATH + item + ".conf"
        with open(outpath, encoding="utf-8", mode="w") as out_f:
            out_f.write(content)

def usages():
    print(sys.argv[0] + ' -i <CRS-directory> -o <output-directory>')
    sys.exit(2)

def clone_project():
    print("=== git clone %s" % CRS_GIT)
    git.Git().clone(CRS_GIT)
    print("=== git clone done !")

def getopts(argv):
    global CRS_PATH, OUT_PATH
    if len(argv) > 1:
        try:
            opts = getopt.getopt(argv[1:], "hi:o:")
            for opt, arg in opts:
                if opt == '-h':
                    usages()
                elif opt == "-i":
                    CRS_PATH = arg
                elif opt == "-o":
                    OUT_PATH = arg
        except getopt.GetoptError:
            usages()

    if CRS_PATH == "":
        CRS_PATH = "./coreruleset"
        if not os.path.exists(CRS_PATH):
            clone_project()

    else:
        if not os.path.exists(CRS_PATH):
            print("=== ERROR: Invalid crs project path: " + CRS_PATH)
            sys.exit(3)
    
    if OUT_PATH == "":
        OUT_PATH = "./"


if __name__ == '__main__':

    getopts(sys.argv)

    workbook = xlwt.Workbook(encoding = 'utf-8')

    for item in FILE_LIST:
        compress_rules(item)

        worksheet = workbook.add_sheet(item)

        parse_rules(worksheet, item)

    workbook.save('modsecurity-rules.xls')
