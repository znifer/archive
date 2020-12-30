import axios from "axios"

export default class ApiService {

    _apiBase = 'http://localhost:8000/api'
    //_apiBase = 'http://localhost:8080'

    async getResource(url) {
        try{
            const response = await axios({
                method: 'get',
                url: `${this._apiBase}${url}`,

            });
            return response.data;
        }
        catch (e){
            return null
        }
    }


    async getAllAlbums() {
        const res = await this.getResource('/albums/')
        return res
    }

    async getBestAlbums() {
        const res = await this.getResource('/top_albums/')
        return res
    }

    async getAlbum(id) {
        const res = await this.getResource(`/albums/${id}/`)
        return res
    }

    async getAllbands() {
        const res = await this.getResource('/bands/')
        return res
    }

    async getBand(id) {
        const res = await this.getResource(`/bands/${id}/`)
        return res
    }

    async searchBand(searchRequest) {
        const res = await this.getResource(`/bands/?search=${searchRequest}`)
        return res
    }

    async searchAlbum(searchRequest) {
        const res = await this.getResource(`/albums/?search=${searchRequest}`)
        return res
    }

    async getPreferences(){
        const accessToken = localStorage.getItem('access')
        try{
            const response = await axios({
                method: 'get',
                url: `${this._apiBase}/user_preferences/`,
                headers: {
                    "Authorization" : `Bearer ${accessToken}`
                }
            });
            return response.data;
        }
        catch (e){
            return null
        }
    }
}