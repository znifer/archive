import axios from "axios"

export default class AuthService {

    async login(username, password) {
        try {
            const response = await axios({
                method: 'post',
                url: "http://localhost:8000/api/token/",
                data: {
                    username: username,
                    password: password
                }
            })
            const data = await response.data
            window.localStorage.setItem('access', data.access)
            window.localStorage.setItem('refresh', data.refresh)
        }
        catch (e) {
            console.log(e);
        }
    }

    logout() {
        console.log('deleting')
        localStorage.removeItem("access")
        localStorage.removeItem("refresh")
    }

    isLogged() {
        if (localStorage.getItem("access")) {
            return true
        }
        return false
            
    }

    getCurrentUser() {
        return JSON.parse(localStorage.getItem("user"))
    }
}