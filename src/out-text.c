#include "output.h"
#include "masscan.h"

/****************************************************************************
 ****************************************************************************/
static void
text_out_open(struct Output *out, FILE *fp)
{
    UNUSEDPARM(out);
    fprintf(fp, "#masscan\n");
}

/****************************************************************************
 ****************************************************************************/
static void
text_out_close(struct Output *out, FILE *fp)
{
    UNUSEDPARM(out);
    fprintf(fp, "# end\n");
}

/****************************************************************************
 ****************************************************************************/
static void
text_out_status(struct Output *out, FILE *fp, 
    int status, unsigned ip, unsigned port, unsigned reason, unsigned ttl)
{
    UNUSEDPARM(ttl);
    UNUSEDPARM(reason);
    UNUSEDPARM(out);
    

    fprintf(fp, "%s tcp %u %u.%u.%u.%u %u\n",
        status_string(status),
        port,
        (ip>>24)&0xFF,
        (ip>>16)&0xFF,
        (ip>> 8)&0xFF,
        (ip>> 0)&0xFF,
        (unsigned)global_now
        );
}

/*************************************** *************************************
 ****************************************************************************/
static void
text_out_banner(struct Output *out, FILE *fp, unsigned ip, unsigned port, 
        unsigned proto, const unsigned char *px, unsigned length)
{

    UNUSEDPARM(out);

    fprintf(fp, "%s tcp %u %u.%u.%u.%u %u %s %.*s\n",
        "banner",
        port,
        (ip>>24)&0xFF,
        (ip>>16)&0xFF,
        (ip>> 8)&0xFF,
        (ip>> 0)&0xFF,
        (unsigned)global_now,
        proto_string(proto),
        length, px
        );
}


/****************************************************************************
 ****************************************************************************/
const struct OutputType text_output = {
    "txt",
    0,
    text_out_open,
    text_out_close,
    text_out_status,
    text_out_banner
};



