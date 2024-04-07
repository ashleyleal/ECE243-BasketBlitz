
int samples_n = 299258;

struct audio_t {
    volatile unsigned int control;
    volatile unsigned char rarc;
    volatile unsigned char ralc;
    volatile unsigned char wsrc;
    volatile unsigned char wslc;
    volatile unsigned int ldata;
    volatile unsigned int rdata;
};

struct audio_t *const audiop = ((struct audio_t *)0xff203040);

void audio_playback_mono(int *samples, int n) {
    int count = 0;

    audiop->control = 0x8;  // clear the output FIFOs
    audiop->control = 0x0;  // resume input conversion
    while (count < samples_n) {
        // output data if there is space in the output FIFOs
        if ((audiop->wsrc != 0) && (audiop->wslc != 0)) {
            audiop->ldata = samples[count];
            audiop->rdata = samples[count++];
        }
    }
}

int main(void) {
    audio_playback_mono(samples, samples_n);
    while (1)
        ;
}