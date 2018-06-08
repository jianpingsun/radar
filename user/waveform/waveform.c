#include "waveform.h"

uint16_t waveform[SAMPLE_SIZE] = 
{
    0, 4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, 74, 79, 84, 89, 94, 
    99, 104, 109, 114, 119, 124, 129, 134, 139, 144, 149, 154, 159, 164, 169, 174, 179, 184, 189, 193, 
    198, 203, 208, 213, 218, 223, 228, 233, 238, 243, 248, 253, 258, 263, 268, 273, 278, 283, 288, 293, 
    298, 303, 308, 313, 318, 323, 328, 333, 338, 343, 348, 353, 358, 363, 368, 373, 378, 382, 387, 392, 
    397, 402, 407, 412, 417, 422, 427, 432, 437, 442, 447, 452, 457, 462, 467, 472, 477, 482, 487, 492, 
    497, 502, 507, 512, 517, 522, 527, 532, 537, 542, 547, 552, 557, 562, 567, 572, 576, 581, 586, 591, 
    596, 601, 606, 611, 616, 621, 626, 631, 636, 641, 646, 651, 656, 661, 666, 671, 676, 681, 686, 691, 
    696, 701, 706, 711, 716, 721, 726, 731, 736, 741, 746, 751, 756, 761, 765, 770, 775, 780, 785, 790, 
    795, 800, 805, 810, 815, 820, 825, 830, 835, 840, 845, 850, 855, 860, 865, 870, 875, 880, 885, 890, 
    895, 900, 905, 910, 915, 920, 925, 930, 935, 940, 945, 950, 954, 959, 964, 969, 974, 979, 984, 989, 
    994, 999, 1004, 1009, 1014, 1019, 1024, 1029, 1034, 1039, 1044, 1049, 1054, 1059, 1064, 1069, 1074, 1079, 1084, 1089, 
    1094, 1099, 1104, 1109, 1114, 1119, 1124, 1129, 1134, 1139, 1144, 1148, 1153, 1158, 1163, 1168, 1173, 1178, 1183, 1188, 
    1193, 1198, 1203, 1208, 1213, 1218, 1223, 1228, 1233, 1238, 1243, 1248, 1253, 1258, 1263, 1268, 1273, 1278, 1283, 1288, 
    1293, 1298, 1303, 1308, 1313, 1318, 1323, 1328, 1333, 1337, 1342, 1347, 1352, 1357, 1362, 1367, 1372, 1377, 1382, 1387, 
    1392, 1397, 1402, 1407, 1412, 1417, 1422, 1427, 1432, 1437, 1442, 1447, 1452, 1457, 1462, 1467, 1472, 1477, 1482, 1487, 
    1492, 1497, 1502, 1507, 1512, 1517, 1522, 1527, 1531, 1536, 1541, 1546, 1551, 1556, 1561, 1566, 1571, 1576, 1581, 1586, 
    1591, 1596, 1601, 1606, 1611, 1616, 1621, 1626, 1631, 1636, 1641, 1646, 1651, 1656, 1661, 1666, 1671, 1676, 1681, 1686, 
    1691, 1696, 1701, 1706, 1711, 1716, 1720, 1725, 1730, 1735, 1740, 1745, 1750, 1755, 1760, 1765, 1770, 1775, 1780, 1785, 
    1790, 1795, 1800, 1805, 1810, 1815, 1820, 1825, 1830, 1835, 1840, 1845, 1850, 1855, 1860, 1865, 1870, 1875, 1880, 1885, 
    1890, 1895, 1900, 1905, 1909, 1914, 1919, 1924, 1929, 1934, 1939, 1944, 1949, 1954, 1959, 1964, 1969, 1974, 1979, 1984, 
    1989, 1994, 1999, 2004, 2009, 2014, 2019, 2024, 2029, 2034, 2039, 2044, 2049, 2054, 2059, 2064, 2069, 2074, 2079, 2084, 
    2089, 2094, 2099, 2103, 2108, 2113, 2118, 2123, 2128, 2133, 2138, 2143, 2148, 2153, 2158, 2163, 2168, 2173, 2178, 2183, 
    2188, 2193, 2198, 2203, 2208, 2213, 2218, 2223, 2228, 2233, 2238, 2243, 2248, 2253, 2258, 2263, 2268, 2273, 2278, 2283, 
    2288, 2292, 2297, 2302, 2307, 2312, 2317, 2322, 2327, 2332, 2337, 2342, 2347, 2352, 2357, 2362, 2367, 2372, 2377, 2382, 
    2387, 2392, 2397, 2402, 2407, 2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 2477, 2482, 
    2482, 2477, 2472, 2467, 2462, 2457, 2452, 2447, 2442, 2437, 2432, 2427, 2422, 2417, 2412, 2407, 2402, 2397, 2392, 2387, 
    2382, 2377, 2372, 2367, 2362, 2357, 2352, 2347, 2342, 2337, 2332, 2327, 2322, 2317, 2312, 2307, 2302, 2297, 2292, 2288, 
    2283, 2278, 2273, 2268, 2263, 2258, 2253, 2248, 2243, 2238, 2233, 2228, 2223, 2218, 2213, 2208, 2203, 2198, 2193, 2188, 
    2183, 2178, 2173, 2168, 2163, 2158, 2153, 2148, 2143, 2138, 2133, 2128, 2123, 2118, 2113, 2108, 2103, 2099, 2094, 2089, 
    2084, 2079, 2074, 2069, 2064, 2059, 2054, 2049, 2044, 2039, 2034, 2029, 2024, 2019, 2014, 2009, 2004, 1999, 1994, 1989, 
    1984, 1979, 1974, 1969, 1964, 1959, 1954, 1949, 1944, 1939, 1934, 1929, 1924, 1919, 1914, 1909, 1905, 1900, 1895, 1890, 
    1885, 1880, 1875, 1870, 1865, 1860, 1855, 1850, 1845, 1840, 1835, 1830, 1825, 1820, 1815, 1810, 1805, 1800, 1795, 1790, 
    1785, 1780, 1775, 1770, 1765, 1760, 1755, 1750, 1745, 1740, 1735, 1730, 1725, 1720, 1716, 1711, 1706, 1701, 1696, 1691, 
    1686, 1681, 1676, 1671, 1666, 1661, 1656, 1651, 1646, 1641, 1636, 1631, 1626, 1621, 1616, 1611, 1606, 1601, 1596, 1591, 
    1586, 1581, 1576, 1571, 1566, 1561, 1556, 1551, 1546, 1541, 1536, 1531, 1527, 1522, 1517, 1512, 1507, 1502, 1497, 1492, 
    1487, 1482, 1477, 1472, 1467, 1462, 1457, 1452, 1447, 1442, 1437, 1432, 1427, 1422, 1417, 1412, 1407, 1402, 1397, 1392, 
    1387, 1382, 1377, 1372, 1367, 1362, 1357, 1352, 1347, 1342, 1337, 1333, 1328, 1323, 1318, 1313, 1308, 1303, 1298, 1293, 
    1288, 1283, 1278, 1273, 1268, 1263, 1258, 1253, 1248, 1243, 1238, 1233, 1228, 1223, 1218, 1213, 1208, 1203, 1198, 1193, 
    1188, 1183, 1178, 1173, 1168, 1163, 1158, 1153, 1148, 1144, 1139, 1134, 1129, 1124, 1119, 1114, 1109, 1104, 1099, 1094, 
    1089, 1084, 1079, 1074, 1069, 1064, 1059, 1054, 1049, 1044, 1039, 1034, 1029, 1024, 1019, 1014, 1009, 1004, 999, 994, 
    989, 984, 979, 974, 969, 964, 959, 954, 950, 945, 940, 935, 930, 925, 920, 915, 910, 905, 900, 895, 
    890, 885, 880, 875, 870, 865, 860, 855, 850, 845, 840, 835, 830, 825, 820, 815, 810, 805, 800, 795, 
    790, 785, 780, 775, 770, 765, 761, 756, 751, 746, 741, 736, 731, 726, 721, 716, 711, 706, 701, 696, 
    691, 686, 681, 676, 671, 666, 661, 656, 651, 646, 641, 636, 631, 626, 621, 616, 611, 606, 601, 596, 
    591, 586, 581, 576, 572, 567, 562, 557, 552, 547, 542, 537, 532, 527, 522, 517, 512, 507, 502, 497, 
    492, 487, 482, 477, 472, 467, 462, 457, 452, 447, 442, 437, 432, 427, 422, 417, 412, 407, 402, 397, 
    392, 387, 382, 378, 373, 368, 363, 358, 353, 348, 343, 338, 333, 328, 323, 318, 313, 308, 303, 298, 
    293, 288, 283, 278, 273, 268, 263, 258, 253, 248, 243, 238, 233, 228, 223, 218, 213, 208, 203, 198, 
    193, 189, 184, 179, 174, 169, 164, 159, 154, 149, 144, 139, 134, 129, 124, 119, 114, 109, 104, 99, 
    94, 89, 84, 79, 74, 69, 64, 59, 54, 49, 44, 39, 34, 29, 24, 19, 14, 9, 4, 0,  
//  0, 455, 910, 1365, 1820, 2275, 2730, 3185, 3640, 4095, 
};

static void waveformOutputDmaInit()
{
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC->AHB1ENR |= RCC_AHB1Periph_DMA1;
    
    DMA_InitStructure.DMA_BufferSize = SAMPLE_SIZE;
    DMA_InitStructure.DMA_Channel = DMA_Channel_7;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)(&waveform[0]);
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DAC->DHR12R1);
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    
    DMA_Init(DMA1_Stream5,&DMA_InitStructure);
    DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,DISABLE);
    
    DMA_Cmd(DMA1_Stream5,ENABLE); 
}

static void waveformOutputTimerInit()
{
    RCC->APB1ENR |= RCC_APB1Periph_TIM6;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 191;              
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
    TIM_Cmd(TIM6,ENABLE);
}


void waveformOutputDacInit()
{
    DAC_InitTypeDef DAC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC->APB1ENR |= RCC_APB1Periph_DAC;
    RCC->AHB1ENR |= RCC_AHB1Periph_GPIOA;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_Init(DAC_Channel_1,&DAC_InitStructure);
    waveformOutputTimerInit();
    waveformOutputDmaInit();
    DAC_Cmd(DAC_Channel_1,ENABLE);
    DAC_DMACmd(DAC_Channel_1,ENABLE);
}
