#include <stdio.h>

void app_main(void)
{
    extern const unsigned char indexHtml[] asm("_binary_index_html_start");
    printf("html = %s\n", indexHtml);

    extern const unsigned char imgStart[] asm("_binary_esp_idf_start");
    extern const unsigned char imgEnd[] asm("_binary_esp_idf_end");
    const unsigned int imgSize = imgEnd - imgStart;
    printf("img size is %d\n", imgSize);
}
