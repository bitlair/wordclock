<template>
  <div>
    In deze stand verandert de woord klok ieder uur naar een andere kleur. 

    <div v-for="(hour, index) in hours" v-bind:key="index" class="form-group row">
      <label class="col-sm-2 col-form-label">{{ hour }}</label>
      <hue-slider class="col-sm-10" :value="hourlyHues[index]" @input="updateHourlyHue(index, $event)" />
    </div>

    <br /><br /><br />
    <button class="btn btn-primary"  v-on:click="save">Opslaan</button>
  </div>
</template>

<script>
import HueSlider from '@/components/HueSlider.vue'

export default {
  name: 'ColorsHourly',
  computed: {
    hourlyHues: {
      get () {
        return this.$store.state.leds.hourlyHues
      },
    },
    hours: { get() {     
              return [ '00:xx', '01:xx', '02:xx', '03:xx', '04:xx', '05:xx', 
               '06:xx', '07:xx', '08:xx', '09:xx', '10:xx', '11:xx', 
               '12:xx', '13:xx', '14:xx', '15:xx', '16:xx', '17:xx',
               '18:xx', '19:xx', '20:xx', '21:xx', '22:xx', '23:xx' ]
            }}
  },
  components: {
    HueSlider
  },
  methods: {
    updateHourlyHue(index, hue) {
      this.axios.get('/api/led/test', { params: { hue: hue }} )
      this.$store.commit('hourlyHue', { index: index, hue: hue })
    },
    save() {
      var params = {}
      var index = 0
      for (const value of this.hourlyHues) {
        params["h" + index] = value
        index++
      }
      this.axios.get('/api/led/hourlyColors', { params: params })

    }
  }
}
</script>
