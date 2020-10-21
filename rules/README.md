# Rules Database

We will release the rules database in a json file. All rules in an josn array.

```json
{
  "version": "0.0.1",
  "rules": [
    {
      "id": 1001,
      "cve-id": "CVE-2020-1001",
      "pattern": "AAAAAAAAAAAAAA",
      "flags": "i",
      "level": "high",
      "category": "SQL Injection",
      "description": "Descriptive information"
    },
    {
      "id": 1002,
      "cve-id": "CVE-2020-1002",
      "pattern": "AAAAAAAAAAAAAA",
      "flags": "up",
      "level": "medium",
      "category": "XSS",
      "description": "Descriptive information"
    },
    {
      "id": 1003,
      "cve-id": "CVE-2020-1003",
      "pattern": "AAAAAAAAAAAAAA",
      "flags": "im",
      "level": "low",
      "category": "CSRF",
      "description": "Descriptive information"
    }
  ]
}
```

## Pattern

We use [hyperscan](https://github.com/intel/hyperscan) to do the scanning, so all the rules are [regular expression patterns](https://en.wikipedia.org/wiki/Regular_expression). `Hyperscan` supports the pattern syntax used by the `PCRE`  library, described at [HERE](http://www.pcre.org/). However, not all constructs available in libpcre are supported.  See detail in [Compiling Patterns](http://intel.github.io/hyperscan/dev-reference/compilation.html#pattern-support).

## Flags

Flags are used to determine the type of compilation.

| Flag  | Hyperscan Value                                                                                              | Remark                                                  |
| ----- | ------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------- |
| `'i'` | [HS_FLAG_CASELESS](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_CASELESS)         | Set case-insensitive matching                           |
| `'d'` | [HS_FLAG_DOTALL](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_DOTALL)             | Matching a `.` will not exclude newlines.               |
| `'m'` | [HS_FLAG_MULTILINE](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_MULTILINE)       | Set multi-line anchoring.                               |
| `'s'` | [HS_FLAG_SINGLEMATCH](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_SINGLEMATCH)   | Set single-match only mode.                             |
| `'e'` | [HS_FLAG_ALLOWEMPTY](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_ALLOWEMPTY)     | Allow expressions that can match against empty buffers. |
| `'u'` | [HS_FLAG_UTF8](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_UTF8)                 | Enable UTF-8 mode for this expression.                  |
| `'p'` | [HS_FLAG_UCP](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_UCP)                   | Enable Unicode property support for this expression.    |
| `'f'` | [HS_FLAG_PREFILTER](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_PREFILTER)       | Enable prefiltering mode for this expression.           |
| `'l'` | [HS_FLAG_SOM_LEFTMOST](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_SOM_LEFTMOST) | Enable leftmost start of match reporting.               |
| `'c'` | [HS_FLAG_COMBINATION](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_COMBINATION)   | Logical combination.                                    |
| `'q'` | [HS_FLAG_QUIET](http://intel.github.io/hyperscan/dev-reference/api_files.html#c.HS_FLAG_QUIET)               | Don't do any match reporting.                           |

## Level

Rules have 4 Level:

| LeveL    | Description  | Remark                                    |
| -------- | ------------ | ----------------------------------------- |
| `high`   | high risk    | -                                         |
| `medium` | medium risk  | -                                         |
| `low`    | low risk     | -                                         |
| `trial`  | strict rules | strict rules may cause false interception |

## Category

Rules have  many categroies:

| category    | sub-category        | Description                | Remark                                                          |
| ----------- | ------------------- | -------------------------- | --------------------------------------------------------------- |
| `Injection` | `SQL Injection`     |                            |                                                                 |
|             | `Code Injection`    |                            |                                                                 |
|             | `CMD Injection`     |                            |                                                                 |
|             | `XPath Injection`   |                            |                                                                 |
|             | `CSV Injection`     |                            |                                                                 |
|             | `Comment Injection` |                            |                                                                 |
| `XSS`       |                     | Cross-site scripting       | [XSS](https://owasp.org/www-community/attacks/xss/)             |
| `CSRF`      |                     | Cross Site Request Forgery | [CSRF](https://owasp.org/www-community/attacks/csrf)            |
| `RFI`       |                     | Remote file inclusion      |                                                                 |
| `LFI`       |                     | Local file inclusion       |                                                                 |
| `RDF`       |                     | Reflected File Download    | [RDF](https://wiki.owasp.org/index.php/Reflected_File_Download) |

[Attacks on Software Application Security | OWASP Foundation](https://owasp.org/www-community/attacks/)

## Other Rules

[NAXSI:Nginx Anti XSS & SQL Injection](https://github.com/nbs-system/naxsi)

[OWASP ModSecurity Core Rule Set](https://github.com/coreruleset/coreruleset)
