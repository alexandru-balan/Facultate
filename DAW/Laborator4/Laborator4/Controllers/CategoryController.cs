using Laborator4.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Laborator4.Controllers
{
    public class CategoryController : Controller
    {
        private CategoryDbContext db = new CategoryDbContext();
        // GET: Category
        public ActionResult Index()
        {
            var Categories = from category in db.Categories
                             orderby category.CategoryId
                             select category;

            ViewBag.Categories = Categories;

            return View();
        }

        [HttpGet]
        public ActionResult Show (int id)
        {
            db.Categories.Include("Articles");
            var Category = db.Categories.Find(id);

            ViewBag.Category = Category;
            ViewBag.Articles = Category.Articles;

            return View();
        }

        [HttpGet]
        public ActionResult New ()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New (Category category)
        {
            try
            {
                db.Categories.Add(category);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch (Exception ex)
            {
                return View();
            }
        }

        [HttpGet]
        public ActionResult Edit (int id)
        {
            return View();
        }

        [HttpPut]
        public ActionResult Edit (int id, Category category)
        {
            try
            {
                Category category1 = db.Categories.Find(id);

                if (TryUpdateModel(category1))
                {
                    category1.CategoryName = category.CategoryName;
                    db.SaveChanges();
                }
                return RedirectToAction("Index");
            }
            catch (Exception e)
            {
                return View();
            }
        }

        [HttpDelete]
        public ActionResult Delete (int id)
        {
            Category category = db.Categories.Find(id);

            db.Categories.Remove(category);
            db.SaveChanges();

            return RedirectToAction("Index");
        }
    }
}