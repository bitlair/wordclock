<template>
  <div>
    In deze stand is het mogelijk om ieder woord van een aparte kleur te voorzien.
    <br /><br />

    <form>
      <h3>Algemeen</h3>

      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Het</label> 
        <hue-slider class="col-sm-10" :value="leds.wordHues[0]" @input="updateWordHue(0, $event)" />
      </div>

      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Is</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[1]" @input="updateWordHue(1, $event)" />
      </div>

      <h3>Minuten</h3>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Vijf</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[2]" @input="updateWordHue(2, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Tien</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[3]" @input="updateWordHue(3, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Kwart</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[4]" @input="updateWordHue(4, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Voor</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[6]" @input="updateWordHue(6, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Over</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[5]" @input="updateWordHue(5, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Half</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[8]" @input="updateWordHue(8, $event)" />
      </div>

      <h3>Stippen</h3>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Een minuut </label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[9]" @input="updateWordHue(9, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Twee minuten</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[10]" @input="updateWordHue(10, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Drie minuten</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[11]" @input="updateWordHue(11, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Vier minuten</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[12]" @input="updateWordHue(12, $event)" />
      </div>

      <h3>Uren</h3>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Heel uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[7]" @input="updateWordHue(7, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Een uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[13]" @input="updateWordHue(13, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Twee uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[14]" @input="updateWordHue(14, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Drie uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[15]" @input="updateWordHue(15, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Vier uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[16]" @input="updateWordHue(16, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Vijf uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[17]" @input="updateWordHue(17, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Zes uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[18]" @input="updateWordHue(18, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Zeven uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[19]" @input="updateWordHue(19, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Acht uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[20]" @input="updateWordHue(20, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Negen uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[21]" @input="updateWordHue(21, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Tien uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[22]" @input="updateWordHue(22, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Elf uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[23]" @input="updateWordHue(23, $event)" />
      </div>
      <div class="form-group row">
        <label class="col-sm-2 col-form-label">Twaalf uur</label>
        <hue-slider class="col-sm-10" :value="leds.wordHues[24]" @input="updateWordHue(24, $event)" />
      </div>

      <br /><br /><br />
      <button class="btn btn-primary" v-on:click="save">Opslaan</button>
    </form>
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
