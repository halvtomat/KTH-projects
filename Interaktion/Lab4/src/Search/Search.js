import React, { Component } from "react";
import "./Search.css";

class Search extends Component {
    constructor(props) {
        super(props);
        this.keyword = "Pizza";
        this.query = "All"
    }

    setKeyword(evt){
        this.keyword = evt.target.value;
    }
    setQuery = (evt) => {
        this.query = evt.target.value;
    }

    render() {
        return (
        <div className="Search">
          <h2 id="topText">This is the Search screen</h2>
          <input type="text" id="keyWords" placeholder="Enter key words" onChange={evt => this.setKeyword(evt)}></input>
          <button type="submit" className="button" id="submit" onClick={() => this.props.searchDishes(this.keyword, this.query)}>search</button>
          <select id="select" onChange={evt => this.setQuery(evt)}>
            <option value="All">All</option>
            <option value="Main Course">Main Course</option>
            <option value="Side Dish">Side Dish</option>
            <option value="Dessert">Dessert</option>
            <option value="Appetizer">Appetizer</option>
          </select>
        </div>
        );
    }
}

export default Search;
