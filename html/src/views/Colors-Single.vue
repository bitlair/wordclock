<template>
  <div>
    In deze stand is de woordklok altijd dezelfde kleur. 
    <hue-slider v-model="singleHue" />
    <br /><br /><br />
    <button v-on:click="save">Opslaan</button>
  </div>
</template>

<script>
import HueSlider from '@/components/HueSlider.vue'

export default {
  name: 'ColorsSingle',
  computed: {
    singleHue: {
      get () {
        return this.$store.state.leds.singleHue
      },
      set (value) {
        this.axios.get('/api/led/test', { params: { hue: value }} )
        this.$store.commit('singleHue', value)
      }
    }
  },
  components: {
    HueSlider
  },
  methods: {
    save() {
      this.axios.get('api/led/singleColor', { params: { hue: this.$store.state.leds.singleHue }} )
    }
  }
}
</script>