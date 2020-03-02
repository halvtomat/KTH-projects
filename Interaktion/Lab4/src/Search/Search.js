import React, { Component } from "react";
import "./Search.css";

class Search extends Component {
    constructor(props) {
        super(props);
    }

    componentDidMount() {
        this.props.model.addObserver(this);
    }
    componentWillUnmount() {
        this.props.model.removeObserver(this);
    }

    render() {
        return (
        <div className="Search">
          <h2 id="topText">This is the Search screen</h2>
          <input type="text" id="keyWords" placeholder="Enter key words"></input>
          <button type="submit" id="submit" className="button">search</button>
          <select id="select">
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
