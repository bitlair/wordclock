<template>
  <div>
    In deze stand is het mogelijk om ieder woord van een aparte kleur te voorzien.
    <br /><br />

    <b>Algemeen</b><br>
    Het <hue-slider :value="leds.wordHues[0]" @input="updateWordHue(0, $event)" /><br />
    Is <hue-slider :value="leds.wordHues[1]" @input="updateWordHue(1, $event)" /><br />

    <b>Minuten</b>
    Vijf  <hue-slider :value="leds.wordHues[2]" @input="updateWordHue(2, $event)" /><br />
    Tien  <hue-slider :value="leds.wordHues[3]" @input="updateWordHue(3, $event)" /><br />
    Kwart  <hue-slider :value="leds.wordHues[4]" @input="updateWordHue(4, $event)" /><br />
    Voor  <hue-slider :value="leds.wordHues[6]" @input="updateWordHue(6, $event)" /><br />
    Over  <hue-slider :value="leds.wordHues[5]" @input="updateWordHue(5, $event)" /><br />
    Half  <hue-slider :value="leds.wordHues[8]" @input="updateWordHue(8, $event)" /><br />

    <b>Stippen</b>
    Een minuut   <hue-slider :value="leds.wordHues[9]" @input="updateWordHue(9, $event)" /><br />
    Twee minuten  <hue-slider :value="leds.wordHues[10]" @input="updateWordHue(10, $event)" /><br />
    Drie minuten  <hue-slider :value="leds.wordHues[11]" @input="updateWordHue(11, $event)" /><br />
    Vier minuten  <hue-slider :value="leds.wordHues[12]" @input="updateWordHue(12, $event)" /><br />

    <b>Uren</b>
    Heel uur  <hue-slider :value="leds.wordHues[7]" @input="updateWordHue(7, $event)" /><br />
    Een uur  <hue-slider :value="leds.wordHues[13]" @input="updateWordHue(13, $event)" /><br />
    Twee uur  <hue-slider :value="leds.wordHues[14]" @input="updateWordHue(14, $event)" /><br />
    Drie uur  <hue-slider :value="leds.wordHues[15]" @input="updateWordHue(15, $event)" /><br />
    Vier uur  <hue-slider :value="leds.wordHues[16]" @input="updateWordHue(16, $event)" /><br />
    Vijf uur  <hue-slider :value="leds.wordHues[17]" @input="updateWordHue(17, $event)" /><br />
    Zes uur  <hue-slider :value="leds.wordHues[18]" @input="updateWordHue(18, $event)" /><br />
    Zeven uur  <hue-slider :value="leds.wordHues[19]" @input="updateWordHue(19, $event)" /><br />
    Acht uur  <hue-slider :value="leds.wordHues[20]" @input="updateWordHue(20, $event)" /><br />
    Negen uur  <hue-slider :value="leds.wordHues[21]" @input="updateWordHue(21, $event)" /><br />
    Tien uur  <hue-slider :value="leds.wordHues[22]" @input="updateWordHue(22, $event)" /><br />
    Elf uur  <hue-slider :value="leds.wordHues[23]" @input="updateWordHue(23, $event)" /><br />
    Twaalf uur  <hue-slider :value="leds.wordHues[24]" @input="updateWordHue(24, $event)" /><br />

    <br /><br /><br />
    <button v-on:click="save">Opslaan</button>

  </div>
</template>

<script>

import { mapState } from 'vuex'
import HueSlider from '@/components/HueSlider.vue'

export default {
  name: 'ColorsWords',
  computed: mapState([ 'leds' ]),
  components: {
    HueSlider
  },
  methods: {
    updateWordHue(wordIndex, value) {
      this.axios.get('/api/led/testWord', { params: { hue: value, word: wordIndex }} )
      this.$store.commit('wordHue', { index: wordIndex, hue: value })
    },
    save() {
      var params = {}
      var index = 0
      for (const value of this.leds.wordHues) {
        params["w" + index] = value
        index++
      }
      this.axios.get('/api/led/wordColors', { params: params })
    }
  }
}
</script>
