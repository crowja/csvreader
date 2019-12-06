# Dev notes for csvreader

Something to consider from RFC 4180, [Common Format and MIME Type for CSV
Files](https://tools.ietf.org/html/rfc4180), October 2005:

    The ABNF grammar appears as follows:

       file = [header CRLF] record *(CRLF record) [CRLF]
       header = name *(COMMA name)
       record = field *(COMMA field)
       name = field
       field = (escaped / non-escaped)
       escaped = DQUOTE *(TEXTDATA / COMMA / CR / LF / 2DQUOTE) DQUOTE
       non-escaped = *TEXTDATA
       COMMA = %x2C
       CR = %x0D ;as per section 6.1 of RFC 2234
       DQUOTE =  %x22 ;as per section 6.1 of RFC 2234
       LF = %x0A ;as per section 6.1 of RFC 2234
       CRLF = CR LF ;as per section 6.1 of RFC 2234
       TEXTDATA =  %x20-21 / %x23-2B / %x2D-7E

*   Probably good to take this into account, but we probably want to deal with a
    few other delimiters: SEMICOLON, TAB.
